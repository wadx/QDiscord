/*
 * QDiscord - An unofficial C++ and Qt wrapper for the Discord API.
 * Copyright (C) 2016-2017 george99g
 * Copyright(c) 2022 by wad(wad@inbox.lv)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 */

#include "stdafx.h"
#include "QDiscordMessage.h"
#include "QDiscordInteraction.h"
#include "QDiscordRest.h"
#include "moc_QDiscordMessage.cpp"


QSharedPointer<QDiscordMessageActivity> QDiscordMessageActivity::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordMessageActivity> out(new QDiscordMessageActivity());
	out->deserialize(object);
	return out;
}


QDiscordMessageActivity::QDiscordMessageActivity(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordMessageActivity::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordMessageActivity::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordMessageReference> QDiscordMessageReference::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordMessageReference> out(new QDiscordMessageReference());
	out->deserialize(object);
	return out;
}


QDiscordMessageReference::QDiscordMessageReference(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordMessageReference::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordMessageReference::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordMessage> QDiscordMessage::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordMessage> message(new QDiscordMessage());
	message->deserialize(object);
	return message;
}


QDiscordMessage::QDiscordMessage(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordMessage::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
	// The channel pointer is handled by the calling class
}


QJsonObject QDiscordMessage::serialize() const
{
	return serializeJson();
}


void QDiscordMessage::create(QDiscordRest& rest, const QDiscordID& channel, const QFileInfo& file, const QJsonObject& data, const std::function<void(QSharedPointer<QDiscordMessage>)>& callback)
{
	QFile* fileDevice = new QFile(file.canonicalFilePath());
	if (!fileDevice->open(QFile::ReadOnly))
	{
		delete fileDevice;
		if (callback)
		{
			callback(QSharedPointer<QDiscordMessage>());
		}
		return;
	}

	QSharedPointer<QHttpMultiPart> multiPart = QSharedPointer<QHttpMultiPart>(new QHttpMultiPart(QHttpMultiPart::FormDataType));
	fileDevice->setParent(multiPart.get());

	QHttpPart payloadPart;
	payloadPart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"payload_json\"");
	payloadPart.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	payloadPart.setBody(QJsonDocument(data).toJson());
	multiPart->append(payloadPart);

	QHttpPart filePart;
	filePart.setHeader(QNetworkRequest::ContentDispositionHeader, R"(form-data; name="file"; filename=")" + QUrl::toPercentEncoding(file.fileName()) + "\"");
	filePart.setHeader(QNetworkRequest::ContentTypeHeader, QMimeDatabase().mimeTypeForFile(file).name());
	filePart.setBodyDevice(fileDevice);
	multiPart->append(filePart);

	rest.request(QDiscordRoutes::Messages::sendMessage(channel), multiPart.get(), [multiPart, callback](QNetworkReply* reply) // keep multiPart for proper deleting
	{
		if (callback)
		{
			if (reply->error() != QNetworkReply::NoError)
			{
				callback(QSharedPointer<QDiscordMessage>());
				return;
			}
			callback(QDiscordMessage::fromJson(QJsonDocument::fromJson(reply->readAll()).object()));
		}
	});
}


void QDiscordMessage::sendCreate(QDiscordRest& rest, const QDiscordID& channelId, const std::function<void(QSharedPointer<QDiscordMessage>)>& callback)
{
	if (_content.isEmpty() && _components.isEmpty() && _attachments.isEmpty() && _embeds.isEmpty())
	{
		AssertMessage("QDiscordMessage::sendCreate() - Message content, components, attachments and embeds empty");
		return;
	}
	if (_attachments.isEmpty())
	{
		QJsonObject data = serialize();
		rest.request(QDiscordRoutes::Messages::sendMessage(channelId), data, [callback](QNetworkReply* reply)
		{
			if (callback)
			{
				if (reply->error() != QNetworkReply::NoError)
				{
					callback(QSharedPointer<QDiscordMessage>());
					return;
				}
				QSharedPointer<QDiscordMessage> message = QDiscordMessage::fromJson(QJsonDocument::fromJson(reply->readAll()).object());
				callback(message);
			}
		});
	}
	else
	{
		AssertErrorRetVoid(_attachments.size() == _files.size(), "QDiscordMessage::sendCreate() - Sizes of attachments and files are different");
		QSharedPointer<QHttpMultiPart> multiPart = QSharedPointer<QHttpMultiPart>(new QHttpMultiPart(QHttpMultiPart::FormDataType));
		QJsonObject data = serialize();
		QHttpPart payloadPart;
		payloadPart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"payload_json\"");
		payloadPart.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
		payloadPart.setBody(QJsonDocument(data).toJson());
		//AssertDumpJsonObject("send", data);
		multiPart->append(payloadPart);
		for (qsizetype pos = 0; pos < _attachments.size(); pos++)
		{
			QSharedPointer<QDiscordAttachment> attachment = _attachments[pos];
			const QByteArray& fileData = _files[pos];
			QHttpPart filePart;
			filePart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"files[" + attachment->id().toString() + "]\"; filename=\"" + QUrl::toPercentEncoding(attachment->filename()) + "\"");
			if (attachment->content_type().has_value())
			{
				filePart.setHeader(QNetworkRequest::ContentTypeHeader, attachment->content_type().value());
			}
			else
			{
				filePart.setHeader(QNetworkRequest::ContentTypeHeader, QMimeDatabase().mimeTypeForData(fileData).name());
			}
			filePart.setBody(fileData);
			multiPart->append(filePart);
		}
		rest.request(QDiscordRoutes::Messages::sendMessage(channelId), multiPart.get(), [multiPart, callback](QNetworkReply* reply) // keep multiPart for proper deleting
		{
			if (callback)
			{
				if (reply->error() != QNetworkReply::NoError)
				{
					callback(QSharedPointer<QDiscordMessage>());
					return;
				}
				callback(QDiscordMessage::fromJson(QJsonDocument::fromJson(reply->readAll()).object()));
			}
		});
	}
}


void QDiscordMessage::sendEdit(QDiscordRest& rest, const QDiscordID& channelId, const std::function<void(QSharedPointer<QDiscordMessage>)>& callback)
{
	if (!_id)
	{
		AssertMessage("QDiscordMessage::sendEdit() - No message id");
		return;
	}
	if (_attachments.isEmpty())
	{
		QJsonObject data = serialize();
		rest.request(QDiscordRoutes::Messages::editMessage(channelId, _id), data, [callback](QNetworkReply* reply)
		{
			if (callback)
			{
				if (reply->error() != QNetworkReply::NoError)
				{
					callback(QSharedPointer<QDiscordMessage>());
					return;
				}
				QSharedPointer<QDiscordMessage> message = QDiscordMessage::fromJson(QJsonDocument::fromJson(reply->readAll()).object());
				callback(message);
			}
		});
	}
	else
	{
		AssertErrorRetVoid(_attachments.size() == _files.size(), "QDiscordMessage::sendEdit() - Sizes of attachments and files are different");
		QSharedPointer<QHttpMultiPart> multiPart = QSharedPointer<QHttpMultiPart>(new QHttpMultiPart(QHttpMultiPart::FormDataType));
		QJsonObject data = serialize();
		QHttpPart payloadPart;
		payloadPart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"payload_json\"");
		payloadPart.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
		payloadPart.setBody(QJsonDocument(data).toJson());
		//AssertDumpJsonObject("send", data);
		multiPart->append(payloadPart);
		for (qsizetype pos = 0; pos < _attachments.size(); pos++)
		{
			QSharedPointer<QDiscordAttachment> attachment = _attachments[pos];
			const QByteArray& fileData = _files[pos];
			QHttpPart filePart;
			filePart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"files[" + attachment->id().toString() + "]\"; filename=\"" + QUrl::toPercentEncoding(attachment->filename()) + "\"");
			if (attachment->content_type().has_value())
			{
				filePart.setHeader(QNetworkRequest::ContentTypeHeader, attachment->content_type().value());
			}
			else
			{
				filePart.setHeader(QNetworkRequest::ContentTypeHeader, QMimeDatabase().mimeTypeForData(fileData).name());
			}
			filePart.setBody(fileData);
			multiPart->append(filePart);
		}
		rest.request(QDiscordRoutes::Messages::editMessage(channelId, _id), multiPart.get(), [multiPart, callback](QNetworkReply* reply) // keep multiPart for proper deleting
		{
			if (callback)
			{
				if (reply->error() != QNetworkReply::NoError)
				{
					callback(QSharedPointer<QDiscordMessage>());
					return;
				}
				callback(QDiscordMessage::fromJson(QJsonDocument::fromJson(reply->readAll()).object()));
			}
		});
	}
}


void QDiscordMessage::remove(QDiscordRest& rest, const QDiscordID& channelId, const QDiscordID& messageId, const std::function<void(bool)>& callback)
{
	rest.request(QDiscordRoutes::Messages::deleteMessage(channelId, messageId), [callback](QNetworkReply* reply)
	{
		if (callback)
		{
			callback(reply->error() == 204);
		}
	});
}


void QDiscordMessage::bulkRemove(QDiscordRest& rest, const QDiscordID& channel, const QList<QDiscordID>& messageIds, const std::function<void(bool)>& callback)
{
	QJsonObject data;
	QJsonArray array;
	for (const QDiscordID& message : messageIds)
	{
		array.append(message.toString());
	}
	data["messages"] = array;
	rest.request(QDiscordRoutes::Messages::deleteMessages(channel), data, [callback](QNetworkReply* reply)
	{
		if (callback)
		{
			callback(reply->error() == 204);
		}
	});
}


void QDiscordMessage::get(QDiscordRest& rest, const QDiscordID& channelId, const QDiscordID& messageId, const std::function<void(QSharedPointer<QDiscordMessage>)>& callback)
{
	rest.request(QDiscordRoutes::Messages::getMessage(channelId, messageId), [&rest, callback](QNetworkReply* reply)
	{
		if (callback)
		{
			if (reply->error() != QNetworkReply::NoError)
			{
				callback(QSharedPointer<QDiscordMessage>());
			}
			else
			{
				QSharedPointer<QDiscordMessage> message = QDiscordMessage::fromJson(QJsonDocument::fromJson(reply->readAll()).object());
				callback(message);
			}
		}
	});
}


void QDiscordMessage::ack(QDiscordRest& rest, const QDiscordID& channelId, const QDiscordID& messageId, const std::function<void(bool)>& callback)
{
	QJsonObject data;
	if (rest.lastAckToken().isEmpty())
	{
		data["token"] = QJsonValue();
	}
	else
	{
		data["token"] = rest.lastAckToken().rawToken();
	}
	rest.request(QDiscordRoutes::Messages::ackMessage(channelId, messageId), data, [&rest, callback](QNetworkReply* reply)
	{
		if (reply->error() == QNetworkReply::NoError)
		{
			rest.setLastAckToken(QDiscordToken(QJsonDocument::fromJson(reply->readAll()).object()["token"].toString(), QDiscordToken::Type::None));
			if (callback)
			{
				callback(true);
			}
		}
		else
		{
			if (callback)
			{
				callback(false);
			}
		}
	});
}


void QDiscordMessage::sendAck(QDiscordRest& rest, const QDiscordID& channelId, const std::function<void(bool)>& callback)
{
	if (!_id)
	{
		AssertMessage("QDiscordMessage::sendAck() - No message id");
		if (callback)
		{
			callback(false);
		}
		return;
	}
	QJsonObject data;
	if (rest.lastAckToken().isEmpty())
	{
		data["token"] = QJsonValue();
	}
	else
	{
		data["token"] = rest.lastAckToken().rawToken();
	}
	rest.request(QDiscordRoutes::Messages::ackMessage(channelId, _id), data, [&rest, callback](QNetworkReply* reply)
	{
		if (reply->error() == QNetworkReply::NoError)
		{
			rest.setLastAckToken(QDiscordToken(QJsonDocument::fromJson(reply->readAll()).object()["token"].toString(), QDiscordToken::Type::None));
			if (callback)
			{
				callback(true);
			}
		}
		else
		{
			if (callback)
			{
				callback(false);
			}
		}
	});
}


QSharedPointer<QDiscordGuild> QDiscordMessage::guild() const
{
	return _channel ? _channel->guild() : QSharedPointer<QDiscordGuild>();
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, QDiscordMessageActivity::Type& value, const QString& name)
{
	switch (action.data()[name].toInt(-1))
	{
	case 1:
		value = QDiscordMessageActivity::Type::JOIN;
		break;
	case 2:
		value = QDiscordMessageActivity::Type::SPECTATE;
		break;
	case 3:
		value = QDiscordMessageActivity::Type::LISTEN;
		break;
	case 5:
		value = QDiscordMessageActivity::Type::JOIN_REQUEST;
		break;
	default:
		value = QDiscordMessageActivity::Type::Unknown;
	}
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const QDiscordMessageActivity::Type& value, const QString& name)
{
	if (value != QDiscordMessageActivity::Type::Unknown)
	{
		action.data().insert(name, static_cast<int>(value));
	}
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, QDiscordMessage::Type& value, const QString& name)
{
	switch (action.data()[name].toInt(-1))
	{
	case 0:
		value = QDiscordMessage::Type::DEFAULT;
		break;
	case 1:
		value = QDiscordMessage::Type::RECIPIENT_ADD;
		break;
	case 2:
		value = QDiscordMessage::Type::RECIPIENT_REMOVE;
		break;
	case 3:
		value = QDiscordMessage::Type::CALL;
		break;
	case 4:
		value = QDiscordMessage::Type::CHANNEL_NAME_CHANGE;
		break;
	case 5:
		value = QDiscordMessage::Type::CHANNEL_ICON_CHANGE;
		break;
	case 6:
		value = QDiscordMessage::Type::CHANNEL_PINNED_MESSAGE;
		break;
	case 7:
		value = QDiscordMessage::Type::GUILD_MEMBER_JOIN;
		break;
	case 8:
		value = QDiscordMessage::Type::USER_PREMIUM_GUILD_SUBSCRIPTION;
		break;
	case 9:
		value = QDiscordMessage::Type::USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_1;
		break;
	case 10:
		value = QDiscordMessage::Type::USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_2;
		break;
	case 11:
		value = QDiscordMessage::Type::USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_3;
		break;
	case 12:
		value = QDiscordMessage::Type::CHANNEL_FOLLOW_ADD;
		break;
	case 14:
		value = QDiscordMessage::Type::GUILD_DISCOVERY_DISQUALIFIED;
		break;
	case 15:
		value = QDiscordMessage::Type::GUILD_DISCOVERY_REQUALIFIED;
		break;
	case 16:
		value = QDiscordMessage::Type::GUILD_DISCOVERY_GRACE_PERIOD_INITIAL_WARNING;
		break;
	case 17:
		value = QDiscordMessage::Type::GUILD_DISCOVERY_GRACE_PERIOD_FINAL_WARNING;
		break;
	case 18:
		value = QDiscordMessage::Type::THREAD_CREATED;
		break;
	case 19:
		value = QDiscordMessage::Type::REPLY;
		break;
	case 20:
		value = QDiscordMessage::Type::CHAT_INPUT_COMMAND;
		break;
	case 21:
		value = QDiscordMessage::Type::THREAD_STARTER_MESSAGE;
		break;
	case 22:
		value = QDiscordMessage::Type::GUILD_INVITE_REMINDER;
		break;
	case 23:
		value = QDiscordMessage::Type::CONTEXT_MENU_COMMAND;
		break;
	default:
		value = QDiscordMessage::Type::DEFAULT;
		break;
	}
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const QDiscordMessage::Type& value, const QString& name)
{
	action.data().insert(name, static_cast<int>(value));
}


