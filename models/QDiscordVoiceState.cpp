
// Copyright(c) 2022 by wad(wad@inbox.lv)

#include "stdafx.h"
#include "QDiscordVoiceState.h"


QSharedPointer<QDiscordVoiceState> QDiscordVoiceState::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordVoiceState> out(new QDiscordVoiceState());
	out->deserialize(object);
	return out;
}


QDiscordVoiceState::QDiscordVoiceState(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordVoiceState::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordVoiceState::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordVoiceRegion> QDiscordVoiceRegion::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordVoiceRegion> out(new QDiscordVoiceRegion());
	out->deserialize(object);
	return out;
}


QDiscordVoiceRegion::QDiscordVoiceRegion(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordVoiceRegion::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordVoiceRegion::serialize() const
{
	return serializeJson();
}


