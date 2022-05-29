
// Copyright(c) 2022 by wad(wad@inbox.lv)

#include "stdafx.h"
#include "QDiscordWebhook.h"
#include "QDiscordRest.h"
#include "QDiscordRoute.h"


QSharedPointer<QDiscordWebhook> QDiscordWebhook::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordWebhook> out(new QDiscordWebhook());
	out->deserialize(object);
	return out;
}


QDiscordWebhook::QDiscordWebhook(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordWebhook::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordWebhook::serialize() const
{
	return serializeJson();
}


void QDiscordWebhook::sendCreate(QDiscordRest& rest, const QDiscordID& applicationId, const QString& interactionToken, const std::optional<bool>& wait, std::optional<QDiscordID>& threadId, const std::function<void(QSharedPointer<QDiscordMessage>)>& callback)
{
	if (!_content.has_value() && _attachments.isEmpty() && _embeds.isEmpty())
	{
		AssertMessage("QDiscordWebhook::sendCreate() - Required one of: content, file, embeds");
		if (callback)
		{
			callback(QSharedPointer<QDiscordMessage>());
		}
		return;
	}
	QJsonObject data = serialize();
	QDiscordRoute route = QDiscordRoutes::Interactions::createFollowupMessage(applicationId, interactionToken);
	QUrlQuery query;
	if (wait.has_value())
	{
		query.addQueryItem("wait", wait.value() ? "true" : "false"); // waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that is not saved does not return an error) (always true in follow up messages)
	}
	if (threadId.has_value())
	{
		query.addQueryItem("thread_id", threadId.value().toString()); // Send a message to the specified thread within a webhook's channel. The thread will automatically be unarchived.	(not supported in fullow up messages)
	}
	if (!query.isEmpty())
	{
		route.setQuery(query);
	}
	rest.request(route, data, [callback](QNetworkReply* reply)
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


