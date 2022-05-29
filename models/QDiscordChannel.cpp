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
#include "QDiscordChannel.h"
#include "QDiscordGuild.h"
#include "QDiscordMessage.h"
#include "QDiscordRest.h"


QSharedPointer<QDiscordThreadMetadata> QDiscordThreadMetadata::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordThreadMetadata> out(new QDiscordThreadMetadata());
	out->deserialize(object);
	return out;
}


QDiscordThreadMetadata::QDiscordThreadMetadata(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordThreadMetadata::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordThreadMetadata::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordThreadMember> QDiscordThreadMember::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordThreadMember> out(new QDiscordThreadMember());
	out->deserialize(object);
	return out;
}


QDiscordThreadMember::QDiscordThreadMember(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordThreadMember::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordThreadMember::serialize() const
{
	return serializeJson();
}


void QDiscordChannel::get(QDiscordRest& rest, const QDiscordID& channel, const std::function<void(QDiscordChannel)>& callback)
{
	rest.request(QDiscordRoutes::Channels::getChannel(channel), [&rest, callback](QNetworkReply* reply)
	{
		QDiscordChannel channel;
		if (reply->error() != QNetworkReply::NoError)
		{
			callback(channel);
			return;
		}
		channel.deserialize(QJsonDocument::fromJson(reply->readAll()).object());
		callback(channel);
	});
}


void QDiscordChannel::getPrivateChannels(QDiscordRest& rest, const std::function<void(QList<QDiscordChannel>)>& callback)
{
	rest.request(QDiscordRoutes::Self::getPrivateChannels(), [&rest, callback](QNetworkReply* reply)
	{
		QList<QDiscordChannel> channelList;
		if (reply->error() != QNetworkReply::NoError)
		{
			callback(channelList);
			return;
		}
		QJsonArray array = QJsonDocument::fromJson(reply->readAll()).array();
		for (const QJsonValueRef& v : array)
		{
			QDiscordChannel channel(v.toObject());
			channelList.append(channel);
		}
		callback(channelList);
	});
}


void QDiscordChannel::getMessage(QDiscordRest& rest, const QDiscordID& channel, const QDiscordID& message, const std::function<void(QSharedPointer<QDiscordMessage>)>& callback)
{
	QDiscordMessage::get(rest, channel, message, callback);
}


void QDiscordChannel::getMessage(QDiscordRest* rest, const QDiscordID& message, const std::function<void(QSharedPointer<QDiscordMessage>)>& callback)
{
	if (!rest || !_id)
	{
		callback(QSharedPointer<QDiscordMessage>());
		return;
	}

	QDiscordMessage::get(*rest, _id, message, callback);
}

void QDiscordChannel::getMessages(QDiscordRest& rest, const QDiscordID& channel, int limit, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback)
{
	rest.request(QDiscordRoutes::Messages::getMessageHistory(channel, limit), [&rest, callback](QNetworkReply* reply)
	{
		QList<QSharedPointer<QDiscordMessage>> list;
		if (reply->error() != QNetworkReply::NoError)
		{
			callback(list);
			return;
		}
		QJsonArray messageArray = QJsonDocument::fromJson(reply->readAll()).array();
		for (const QJsonValueRef& value : messageArray)
		{
			QSharedPointer<QDiscordMessage> message = QDiscordMessage::fromJson(value.toObject());
			list.append(message);
		}
		callback(list);
	});
}


void QDiscordChannel::getMessages(QDiscordRest& rest, const QDiscordID& channel, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback)
{
	getMessages(rest, channel, 50, callback);
}


void QDiscordChannel::getMessages(QDiscordRest* rest, int limit, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback)
{
	if (!rest || !_id)
	{
		callback(QList<QSharedPointer<QDiscordMessage>>());
		return;
	}

	QDiscordChannel::getMessages(*rest, _id, limit, callback);
}


void QDiscordChannel::getMessages(QDiscordRest* rest, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback)
{
	getMessages(rest, 50, callback);
}


void QDiscordChannel::getMessagesAfter(QDiscordRest& rest, const QDiscordID& channel, const QDiscordID& message, int limit, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback)
{
	rest.request(QDiscordRoutes::Messages::getMessageHistoryAfter(channel, limit, message), [&rest, callback](QNetworkReply* reply)
	{
		QList<QSharedPointer<QDiscordMessage>> list;
		if (reply->error() != QNetworkReply::NoError)
		{
			callback(list);
			return;
		}
		QJsonArray messageArray = QJsonDocument::fromJson(reply->readAll()).array();
		for (const QJsonValueRef& value : messageArray)
		{
			QSharedPointer<QDiscordMessage> message = QDiscordMessage::fromJson(value.toObject());
			list.append(message);
		}
		callback(list);
	});
}


void QDiscordChannel::getMessagesAfter(QDiscordRest& rest, const QDiscordID& channel, const QDiscordID& message, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback)
{
	getMessagesAfter(rest, channel, message, 50, callback);
}


void QDiscordChannel::getMessagesAfter(QDiscordRest* rest, const QDiscordID& message, int limit, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback)
{
	if (!rest || !_id)
	{
		callback(QList<QSharedPointer<QDiscordMessage>>());
		return;
	}
	QDiscordChannel::getMessagesAfter(*rest, _id, message, limit, callback);
}


void QDiscordChannel::getMessagesAfter(QDiscordRest* rest, const QDiscordID& message, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback)
{
	getMessagesAfter(rest, message, 50, callback);
}


void QDiscordChannel::getMessagesBefore(QDiscordRest& rest, const QDiscordID& channel, const QDiscordID& message, int limit, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback)
{
	rest.request(QDiscordRoutes::Messages::getMessageHistoryBefore(channel, limit, message), [&rest, callback](QNetworkReply* reply)
	{
		QList<QSharedPointer<QDiscordMessage>> list;
		if (reply->error() != QNetworkReply::NoError)
		{
			callback(list);
			return;
		}
		QJsonArray messageArray = QJsonDocument::fromJson(reply->readAll()).array();
		for (const QJsonValueRef& value : messageArray)
		{
			QSharedPointer<QDiscordMessage> message = QDiscordMessage::fromJson(value.toObject());
			list.append(message);
		}
		callback(list);
	});
}


void QDiscordChannel::getMessagesBefore(QDiscordRest& rest, const QDiscordID& channel, const QDiscordID& message, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback)
{
	getMessagesBefore(rest, channel, message, 50, callback);
}


void QDiscordChannel::getMessagesBefore(QDiscordRest* rest, const QDiscordID& message, int limit, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback)
{
	if (!rest || !_id)
	{
		callback(QList<QSharedPointer<QDiscordMessage>>());
		return;
	}
	QDiscordChannel::getMessagesBefore(*rest, _id, message, limit, callback);
}


void QDiscordChannel::getMessagesBefore(QDiscordRest* rest, const QDiscordID& message, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback)
{
	getMessagesBefore(rest, message, 50, callback);
}


void QDiscordChannel::getMessagesAround(QDiscordRest& rest, const QDiscordID& channel, const QDiscordID& message, int limit, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback)
{
	rest.request(QDiscordRoutes::Messages::getMessageHistoryAround(channel, limit, message), [&rest, callback](QNetworkReply* reply)
	{
		QList<QSharedPointer<QDiscordMessage>> list;
		if (reply->error() != QNetworkReply::NoError)
		{
			callback(list);
			return;
		}
		QJsonArray messageArray = QJsonDocument::fromJson(reply->readAll()).array();
		for (const QJsonValueRef& value : messageArray)
		{
			QSharedPointer<QDiscordMessage> message = QDiscordMessage::fromJson(value.toObject());
			list.append(message);
		}
		callback(list);
	});
}


void QDiscordChannel::getMessagesAround(QDiscordRest& rest, const QDiscordID& channel, const QDiscordID& message, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback)
{
	getMessagesAround(rest, channel, message, 50, callback);
}


void QDiscordChannel::getMessagesAround(QDiscordRest* rest, const QDiscordID& message, int limit, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback)
{
	if (!rest || !_id)
	{
		callback(QList<QSharedPointer<QDiscordMessage>>());
		return;
	}
	QDiscordChannel::getMessagesAround(*rest, _id, message, limit, callback);
}


void QDiscordChannel::getMessagesAround(QDiscordRest* rest, const QDiscordID& message, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback)
{
	getMessagesAround(rest, message, 50, callback);
}


void QDiscordChannel::modify(QDiscordRest& rest, const QDiscordID& channel, const QJsonObject& data)
{
	rest.request(QDiscordRoutes::Channels::modifyChannel(channel), data);
}


void QDiscordChannel::modify(QDiscordRest& rest, const QDiscordID& channel, const QJsonObject& data, const std::function<void(QDiscordChannel)>& callback)
{
	rest.request(QDiscordRoutes::Channels::modifyChannel(channel), data, [&rest, callback](QNetworkReply* reply)
	{
		QDiscordChannel c;
		if (reply->error() != QNetworkReply::NoError)
		{
			callback(c);
			return;
		}
		c.deserialize(QJsonDocument::fromJson(reply->readAll()).object());
		callback(c);
	});
}


void QDiscordChannel::modify(QDiscordRest* rest, const QJsonObject& data)
{
	if (!rest || !_id)
	{
		return;
	}
	QDiscordChannel::modify(*rest, _id, data);
}


void QDiscordChannel::modify(QDiscordRest* rest, const QJsonObject& data, const std::function<void(QDiscordChannel)>& callback)
{
	if (!rest || !_id)
	{
		callback(QDiscordChannel());
		return;
	}

	QDiscordChannel::modify(*rest, _id, data, callback);
}


void QDiscordChannel::modifyName(QDiscordRest& rest, const QDiscordID& channel, const QString& name)
{
	QJsonObject data = { {"name", name} };
	modify(rest, channel, data);
}


void QDiscordChannel::modifyName(QDiscordRest& rest, const QDiscordID& channel, const QString& name, const std::function<void(QDiscordChannel)>& callback)
{
	QJsonObject data = { {"name", name} };
	modify(rest, channel, data, callback);
}


void QDiscordChannel::modifyName(QDiscordRest* rest, const QString& name)
{
	if (!rest || !_id)
		return;

	QDiscordChannel::modifyName(*rest, _id, name);
}


void QDiscordChannel::modifyName(QDiscordRest* rest, const QString& name, const std::function<void(QDiscordChannel)>& callback)
{
	if (!rest || !_id)
	{
		callback(QDiscordChannel());
		return;
	}

	QDiscordChannel::modifyName(*rest, _id, name, callback);
}


void QDiscordChannel::modifyPosition(QDiscordRest& rest, const QDiscordID& channel, int position)
{
	QJsonObject data = { {"position", position} };
	modify(rest, channel, data);
}


void QDiscordChannel::modifyPosition(QDiscordRest& rest, const QDiscordID& channel, int position, const std::function<void(QDiscordChannel)>& callback)
{
	QJsonObject data = { {"position", position} };
	modify(rest, channel, data, callback);
}


void QDiscordChannel::modifyPosition(QDiscordRest* rest, int position)
{
	if (!rest || !_id)
	{
		return;
	}
	QDiscordChannel::modifyPosition(*rest, _id, position);
}


void QDiscordChannel::modifyPosition(QDiscordRest* rest, int position, const std::function<void(QDiscordChannel)>& callback)
{
	if (!rest || !_id)
	{
		callback(QDiscordChannel());
		return;
	}
	QDiscordChannel::modifyPosition(*rest, _id, position, callback);
}


void QDiscordChannel::modifyTopic(QDiscordRest& rest, const QDiscordID& channel, const QString& topic)
{
	QJsonObject data = { {"topic", topic} };
	modify(rest, channel, data);
}


void QDiscordChannel::modifyTopic(QDiscordRest& rest, const QDiscordID& channel, const QString& topic, const std::function<void(QDiscordChannel)>& callback)
{
	QJsonObject data = { {"topic", topic} };
	modify(rest, channel, data, callback);
}


void QDiscordChannel::modifyTopic(QDiscordRest* rest, const QString& topic)
{
	if (!rest || !_id)
	{
		return;
	}
	QDiscordChannel::modifyTopic(*rest, _id, topic);
}


void QDiscordChannel::modifyTopic(QDiscordRest* rest, const QString& topic, const std::function<void(QDiscordChannel)>& callback)
{
	if (!rest || !_id)
	{
		callback(QDiscordChannel());
		return;
	}

	QDiscordChannel::modifyTopic(*rest, _id, topic, callback);
}


void QDiscordChannel::modifyBitrate(QDiscordRest& rest, const QDiscordID& channel, int bitrate)
{
	QJsonObject data = { {"bitrate", bitrate} };
	modify(rest, channel, data);
}


void QDiscordChannel::modifyBitrate(QDiscordRest& rest, const QDiscordID& channel, int bitrate, const std::function<void(QDiscordChannel)>& callback)
{
	QJsonObject data = { {"bitrate", bitrate} };
	modify(rest, channel, data, callback);
}


void QDiscordChannel::modifyBitrate(QDiscordRest* rest, int bitrate)
{
	if (!rest || !_id)
	{
		return;
	}
	QDiscordChannel::modifyBitrate(*rest, _id, bitrate);
}


void QDiscordChannel::modifyBitrate(QDiscordRest* rest, int bitrate, const std::function<void(QDiscordChannel)>& callback)
{
	if (!rest || !_id)
	{
		callback(QDiscordChannel());
		return;
	}
	QDiscordChannel::modifyBitrate(*rest, _id, bitrate, callback);
}


void QDiscordChannel::modifyUserLimit(QDiscordRest& rest, const QDiscordID& channel, int userLimit)
{
	QJsonObject data = { {"user_limit", userLimit} };
	modify(rest, channel, data);
}


void QDiscordChannel::modifyUserLimit(QDiscordRest& rest, const QDiscordID& channel, int userLimit, const std::function<void(QDiscordChannel)>& callback)
{
	QJsonObject data = { {"user_limit", userLimit} };
	modify(rest, channel, data, callback);
}


void QDiscordChannel::modifyUserLimit(QDiscordRest* rest, int userLimit)
{
	if (!rest || !_id)
	{
		return;
	}
	QDiscordChannel::modifyUserLimit(*rest, _id, userLimit);
}


void QDiscordChannel::modifyUserLimit(QDiscordRest* rest, int userLimit, const std::function<void(QDiscordChannel)>& callback)
{
	if (!rest || !_id)
	{
		callback(QDiscordChannel());
		return;
	}
	QDiscordChannel::modifyUserLimit(*rest, _id, userLimit, callback);
}


void QDiscordChannel::triggerTyping(QDiscordRest& rest, const QDiscordID& channel)
{
	rest.request(QDiscordRoutes::Channels::sendTyping(channel));
}


void QDiscordChannel::triggerTyping(QDiscordRest& rest, const QDiscordID& channel, const std::function<void(bool)>& callback)
{
	rest.request(QDiscordRoutes::Channels::sendTyping(channel), [callback](QNetworkReply* reply)
	{
		callback(reply->error() == 204);
	});
}


void QDiscordChannel::triggerTyping(QDiscordRest* rest)
{
	if (!rest || !_id)
	{
		return;
	}
	QDiscordChannel::triggerTyping(*rest, _id);
}


void QDiscordChannel::triggerTyping(QDiscordRest* rest, const std::function<void(bool)>& callback)
{
	if (!rest || !_id)
	{
		callback(false);
		return;
	}
	QDiscordChannel::triggerTyping(*rest, _id, callback);
}


void QDiscordChannel::remove(QDiscordRest& rest, const QDiscordID& channel)
{
	rest.request(QDiscordRoutes::Channels::deleteChannel(channel));
}


void QDiscordChannel::remove(QDiscordRest& rest, const QDiscordID& channel, const std::function<void(QDiscordChannel)>& callback)
{
	rest.request(QDiscordRoutes::Channels::deleteChannel(channel), [&rest, callback](QNetworkReply* reply)
	{
		QDiscordChannel c;
		if (reply->error() != QNetworkReply::NoError)
		{
			callback(c);
			return;
		}
		c.deserialize(QJsonDocument::fromJson(reply->readAll()).object());
		callback(c);
	});
}


void QDiscordChannel::remove(QDiscordRest* rest)
{
	if (!rest || !_id)
	{
		return;
	}
	QDiscordChannel::remove(*rest, _id);
}


void QDiscordChannel::remove(QDiscordRest* rest, const std::function<void(QDiscordChannel)>& callback)
{
	if (!rest || !_id)
	{
		callback(QDiscordChannel());
		return;
	}
	QDiscordChannel::remove(*rest, _id, callback);
}


QSharedPointer<QDiscordChannel> QDiscordChannel::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordChannel> channel(new QDiscordChannel());
	channel->deserialize(object);
	return channel;
}


QDiscordChannel::QDiscordChannel(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordChannel::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordChannel::serialize() const
{
	return serializeJson();
}


void QDiscordChannel::setGuild(const QSharedPointer<QDiscordGuild>& guild)
{
	_guild = guild;
	if (!_guild)
	{
		_guildId = QDiscordID();
		return;
	}
	_guildId = guild->id();
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, QDiscordChannel::Type& value, const QString& name)
{
	value = static_cast<QDiscordChannel::Type>(action.data()[name].toInt(255));
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const QDiscordChannel::Type& value, const QString& name)
{
	action.data().insert(name, static_cast<int>(value));
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, QList<QDiscordChannel::Type>& value, const QString& name)
{
	value.clear();
	for (const QJsonValue& i : action.data()[name].toArray())
	{
		value.append(static_cast<QDiscordChannel::Type>(i.toInt()));
	}
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const QList<QDiscordChannel::Type>& value, const QString& name)
{
	QJsonArray output;
	for (const QDiscordChannel::Type& i : value)
	{
		output.append(static_cast<int>(i));
	}
	if (output.size() > 0)
	{
		action.data().insert(name, output);
	}
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, std::optional<QDiscordChannel::VideoQualityMode>& value, const QString& name)
{
	if (action.data().contains(name))
	{
		switch (action.data()[name].toInt())
		{
		case 1:
			value = QDiscordChannel::VideoQualityMode::AUTO;
			break;
		case 2:
			value = QDiscordChannel::VideoQualityMode::FULL;
			break;
		}
	}
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const std::optional<QDiscordChannel::VideoQualityMode>& value, const QString& name)
{
	if (value.has_value())
	{
		action.data().insert(name, static_cast<int>(value.value()));
	}
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, std::optional<QDiscordChannel::ChannelFlags>& value, const QString& name)
{
	if (action.data().contains(name))
	{
		switch (action.data()[name].toInt())
		{
		case 1 << 1:
			value = QDiscordChannel::ChannelFlags::PINNED;
			break;
		}
	}
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const std::optional<QDiscordChannel::ChannelFlags>& value, const QString& name)
{
	if (value.has_value())
	{
		if (value.value() == QDiscordChannel::ChannelFlags::PINNED)
		{
			action.data().insert(name, 1 << 1);
		}
	}
}


