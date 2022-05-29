
// Copyright(c) 2022 by wad(wad@inbox.lv)

#include "stdafx.h"
#include "QDiscordEmoji.h"


QSharedPointer<QDiscordEmoji> QDiscordEmoji::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordEmoji> out(new QDiscordEmoji());
	out->deserialize(object);
	return out;
}


QDiscordEmoji::QDiscordEmoji(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordEmoji::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordEmoji::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordReaction> QDiscordReaction::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordReaction> out(new QDiscordReaction());
	out->deserialize(object);
	return out;
}


QDiscordReaction::QDiscordReaction(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordReaction::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordReaction::serialize() const
{
	return serializeJson();
}


