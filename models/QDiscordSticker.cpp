
// Copyright(c) 2022 by wad(wad@inbox.lv)

#include "stdafx.h"
#include "QDiscordSticker.h"


QSharedPointer<QDiscordSticker> QDiscordSticker::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordSticker> out(new QDiscordSticker());
	out->deserialize(object);
	return out;
}


QDiscordSticker::QDiscordSticker(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordSticker::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordSticker::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordStickerItem> QDiscordStickerItem::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordStickerItem> out(new QDiscordStickerItem());
	out->deserialize(object);
	return out;
}


QDiscordStickerItem::QDiscordStickerItem(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordStickerItem::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordStickerItem::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordStickerPack> QDiscordStickerPack::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordStickerPack> out(new QDiscordStickerPack());
	out->deserialize(object);
	return out;
}


QDiscordStickerPack::QDiscordStickerPack(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordStickerPack::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordStickerPack::serialize() const
{
	return serializeJson();
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, QDiscordSticker::Type& value, const QString& name)
{
	switch (action.data()[name].toInt(-1))
	{
	case 1:
		value = QDiscordSticker::Type::STANDARD;
		break;
	case 2:
		value = QDiscordSticker::Type::GUILD;
		break;
	default:
		value = QDiscordSticker::Type::Unknown;
	}
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const QDiscordSticker::Type& value, const QString& name)
{
	action.data().insert(name, static_cast<int>(value));
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, QDiscordSticker::StickerFormat& value, const QString& name)
{
	switch (action.data()[name].toInt(-1))
	{
	case 1:
		value = QDiscordSticker::StickerFormat::PNG;
		break;
	case 2:
		value = QDiscordSticker::StickerFormat::APNG;
		break;
	case 3:
		value = QDiscordSticker::StickerFormat::LOTTIE;
		break;
	default:
		value = QDiscordSticker::StickerFormat::Unknown;
	}
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const QDiscordSticker::StickerFormat& value, const QString& name)
{
	action.data().insert(name, static_cast<int>(value));
}


