
// Copyright(c) 2022 by wad(wad@inbox.lv)

#include "stdafx.h"
#include "QDiscordPresence.h"


QSharedPointer<QDiscordClientStatus> QDiscordClientStatus::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordClientStatus> out(new QDiscordClientStatus());
	out->deserialize(object);
	return out;
}


QDiscordClientStatus::QDiscordClientStatus(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordClientStatus::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordClientStatus::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordActivityTimestamps> QDiscordActivityTimestamps::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordActivityTimestamps> out(new QDiscordActivityTimestamps());
	out->deserialize(object);
	return out;
}


QDiscordActivityTimestamps::QDiscordActivityTimestamps(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordActivityTimestamps::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordActivityTimestamps::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordActivityEmoji> QDiscordActivityEmoji::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordActivityEmoji> out(new QDiscordActivityEmoji());
	out->deserialize(object);
	return out;
}


QDiscordActivityEmoji::QDiscordActivityEmoji(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordActivityEmoji::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordActivityEmoji::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordActivityParty> QDiscordActivityParty::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordActivityParty> out(new QDiscordActivityParty());
	out->deserialize(object);
	return out;
}


QDiscordActivityParty::QDiscordActivityParty(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordActivityParty::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordActivityParty::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordActivityAssets> QDiscordActivityAssets::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordActivityAssets> out(new QDiscordActivityAssets());
	out->deserialize(object);
	return out;
}


QDiscordActivityAssets::QDiscordActivityAssets(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordActivityAssets::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordActivityAssets::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordActivitySecrets> QDiscordActivitySecrets::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordActivitySecrets> out(new QDiscordActivitySecrets());
	out->deserialize(object);
	return out;
}


QDiscordActivitySecrets::QDiscordActivitySecrets(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordActivitySecrets::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordActivitySecrets::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordActivityButtons> QDiscordActivityButtons::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordActivityButtons> out(new QDiscordActivityButtons());
	out->deserialize(object);
	return out;
}


QDiscordActivityButtons::QDiscordActivityButtons(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordActivityButtons::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordActivityButtons::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordActivity> QDiscordActivity::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordActivity> out(new QDiscordActivity());
	out->deserialize(object);
	return out;
}


QDiscordActivity::QDiscordActivity(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordActivity::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordActivity::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordPresence> QDiscordPresence::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordPresence> out(new QDiscordPresence());
	out->deserialize(object);
	return out;
}


QDiscordPresence::QDiscordPresence(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordPresence::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordPresence::serialize() const
{
	return serializeJson();
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, std::optional<std::pair<int, int>>& value, const QString& name)
{
	if (action.data().contains(name))
	{
		auto array = action.data()[name].toArray();
		if (array.size() == 2)
		{
			value = std::make_pair(array.at(0).toInt(), array.at(1).toInt());
		}
	}
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const std::optional<std::pair<int, int>>& value, const QString& name)
{
	if (value.has_value())
	{
		QJsonArray array;
		array.append(QJsonValue(value.value().first));
		array.append(QJsonValue(value.value().second));
		action.data().insert(name, array);
	}
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, QDiscordActivity::ActivityType& value, const QString& name)
{
	switch (action.data()[name].toInt(-1))
	{
	case 0:
		value = QDiscordActivity::ActivityType::Game;
		break;
	case 1:
		value = QDiscordActivity::ActivityType::Streaming;
		break;
	case 2:
		value = QDiscordActivity::ActivityType::Listening;
		break;
	case 3:
		value = QDiscordActivity::ActivityType::Watching;
		break;
	case 4:
		value = QDiscordActivity::ActivityType::Custom;
		break;
	case 5:
		value = QDiscordActivity::ActivityType::Competing;
		break;
	default:
		value = QDiscordActivity::ActivityType::Unknown;
	}
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const QDiscordActivity::ActivityType& value, const QString& name)
{
	action.data().insert(name, static_cast<int>(value));
}


