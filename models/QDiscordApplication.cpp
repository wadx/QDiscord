
// Copyright(c) 2022 by wad(wad@inbox.lv)

#include "stdafx.h"
#include "QDiscordApplication.h"


QSharedPointer<QDiscordInstallParams> QDiscordInstallParams::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordInstallParams> out(new QDiscordInstallParams());
	out->deserialize(object);
	return out;
}


QDiscordInstallParams::QDiscordInstallParams(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordInstallParams::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordInstallParams::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordApplication> QDiscordApplication::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordApplication> out(new QDiscordApplication());
	out->deserialize(object);
	return out;
}


QDiscordApplication::QDiscordApplication(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordApplication::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordApplication::serialize() const
{
	return serializeJson();
}


