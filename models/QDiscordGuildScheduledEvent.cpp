
// Copyright(c) 2022 by wad(wad@inbox.lv)

#include "stdafx.h"
#include "QDiscordGuildScheduledEvent.h"


QSharedPointer<QDiscordGuildScheduledEventEntityMetadata> QDiscordGuildScheduledEventEntityMetadata::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordGuildScheduledEventEntityMetadata> out(new QDiscordGuildScheduledEventEntityMetadata());
	out->deserialize(object);
	return out;
}


QDiscordGuildScheduledEventEntityMetadata::QDiscordGuildScheduledEventEntityMetadata(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordGuildScheduledEventEntityMetadata::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordGuildScheduledEventEntityMetadata::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordGuildScheduledEvent> QDiscordGuildScheduledEvent::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordGuildScheduledEvent> out(new QDiscordGuildScheduledEvent());
	out->deserialize(object);
	return out;
}


QDiscordGuildScheduledEvent::QDiscordGuildScheduledEvent(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordGuildScheduledEvent::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordGuildScheduledEvent::serialize() const
{
	return serializeJson();
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, QDiscordGuildScheduledEvent::PrivacyLevel& value, const QString& name)
{
	switch (action.data()[name].toInt(-1))
	{
	case 2:
		value = QDiscordGuildScheduledEvent::PrivacyLevel::GUILD_ONLY;
		break;
	default:
		value = QDiscordGuildScheduledEvent::PrivacyLevel::Unknown;
	}
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const QDiscordGuildScheduledEvent::PrivacyLevel& value, const QString& name)
{
	action.data().insert(name, static_cast<int>(value));
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, QDiscordGuildScheduledEvent::Status& value, const QString& name)
{
	switch (action.data()[name].toInt(-1))
	{
	case 1:
		value = QDiscordGuildScheduledEvent::Status::SCHEDULED;
		break;
	case 2:
		value = QDiscordGuildScheduledEvent::Status::ACTIVE;
		break;
	case 3:
		value = QDiscordGuildScheduledEvent::Status::COMPLETED;
		break;
	case 4:
		value = QDiscordGuildScheduledEvent::Status::CANCELED;
		break;
	default:
		value = QDiscordGuildScheduledEvent::Status::Unknown;
	}
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const QDiscordGuildScheduledEvent::Status& value, const QString& name)
{
	action.data().insert(name, static_cast<int>(value));
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, QDiscordGuildScheduledEvent::EntityType& value, const QString& name)
{
	switch (action.data()[name].toInt(-1))
	{
	case 1:
		value = QDiscordGuildScheduledEvent::EntityType::STAGE_INSTANCE;
		break;
	case 2:
		value = QDiscordGuildScheduledEvent::EntityType::VOICE;
		break;
	case 3:
		value = QDiscordGuildScheduledEvent::EntityType::EXTERNAL;
		break;
	default:
		value = QDiscordGuildScheduledEvent::EntityType::Unknown;
	}
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const QDiscordGuildScheduledEvent::EntityType& value, const QString& name)
{
	action.data().insert(name, static_cast<int>(value));
}


