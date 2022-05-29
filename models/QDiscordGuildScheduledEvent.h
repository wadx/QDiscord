
// Copyright(c) 2022 by wad(wad@inbox.lv)

#pragma once

#include "QDiscordModel.h"
#include "QDiscordId.h"
#include "QDiscordUser.h"


class QDiscordGuildScheduledEventEntityMetadata
	: public QDiscordModelBase<QDiscordGuildScheduledEventEntityMetadata>
{
	Q_GADGET
public:

	static QSharedPointer<QDiscordGuildScheduledEventEntityMetadata> fromJson(const QJsonObject& object);
	QDiscordGuildScheduledEventEntityMetadata(const QJsonObject& object);
	QDiscordGuildScheduledEventEntityMetadata() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._location, "location");
	}

private:
	std::optional<QString> _location; // location of the event (1-100 characters)
};
Q_DECLARE_METATYPE(QDiscordGuildScheduledEventEntityMetadata)


class QDiscordGuildScheduledEvent
	: public QDiscordModelBase<QDiscordGuildScheduledEvent>
{
	Q_GADGET
public:
	enum class PrivacyLevel : qint8
	{
		GUILD_ONLY = 2,
		Unknown    = -1
	};
	Q_ENUM(PrivacyLevel)

	enum class EntityType : qint8
	{
		STAGE_INSTANCE = 1,
		VOICE          = 2,
		EXTERNAL       = 3,
		Unknown        = -1
	};
	Q_ENUM(EntityType)


	enum class Status : qint8
	{
		SCHEDULED = 1,
		ACTIVE    = 2,
		COMPLETED = 3,
		CANCELED  = 4,
		Unknown   = -1
	};
	Q_ENUM(Status)

	static QSharedPointer<QDiscordGuildScheduledEvent> fromJson(const QJsonObject& object);
	QDiscordGuildScheduledEvent(const QJsonObject& object);
	QDiscordGuildScheduledEvent() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._id, "id");
		field(a, self._guild_id, "guild_id");
		field(a, self._channel_id, "channel_id");
		field(a, self._creator_id, "creator_id");
		field(a, self._name, "name");
		field(a, self._description, "description");
		field(a, self._scheduled_start_time, "scheduled_start_time");
		field(a, self._scheduled_end_time, "scheduled_end_time");
		field(a, self._privacy_level, "privacy_level");
		field(a, self._status, "status");
		field(a, self._entity_type, "entity_type");
		field(a, self._entity_id, "entity_id");
		field(a, self._entity_metadata, "entity_metadata");
		field(a, self._creator, "creator");
		field(a, self._user_count, "user_count");
		field(a, self._image, "image");
	}

private:
	QDiscordID                  _id;                   // the id of the scheduled event
	QDiscordID                  _guild_id;             // the guild id which the scheduled event belongs to
	std::optional<QDiscordID>   _channel_id;           // the channel id in which the scheduled event will be hosted, or null if scheduled entity type is EXTERNAL
	std::optional<QDiscordID>   _creator_id;           // the id of the user that created the scheduled event
	QString                     _name;                 // the name of the scheduled event (1-100 characters)
	std::optional<QString>      _description;          // the description of the scheduled event (1-1000 characters)
	QDateTime                   _scheduled_start_time; // the time the scheduled event will start
	std::optional<QDateTime>    _scheduled_end_time;   // timestamp	the time the scheduled event will end, required if entity_type is EXTERNAL
	PrivacyLevel                _privacy_level = PrivacyLevel::Unknown; // the privacy level of the scheduled event
	Status                      _status = Status::Unknown; // the status of the scheduled event
	EntityType                  _entity_type = EntityType::Unknown; // the type of the scheduled event
	std::optional<QDiscordID>   _entity_id;            // the id of an entity associated with a guild scheduled event
	std::optional<QDiscordGuildScheduledEventEntityMetadata> _entity_metadata; // additional metadata for the guild scheduled event
	std::optional<QDiscordUser> _creator;              // the user that created the scheduled event
	std::optional<int>          _user_count;           // the number of users subscribed to the scheduled event
	std::optional<QString>      _image;                // the cover image hash of the scheduled event
};
Q_DECLARE_METATYPE(QDiscordGuildScheduledEvent)


namespace QDiscordModel
{
template<>
void field(QDiscordModel::DeserializeJsonAction& action, QDiscordGuildScheduledEvent::PrivacyLevel& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QDiscordGuildScheduledEvent::PrivacyLevel& value, const QString& name);
template<>
void field(QDiscordModel::DeserializeJsonAction& action, QDiscordGuildScheduledEvent::Status& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QDiscordGuildScheduledEvent::Status& value, const QString& name);
template<>
void field(QDiscordModel::DeserializeJsonAction& action, QDiscordGuildScheduledEvent::EntityType& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QDiscordGuildScheduledEvent::EntityType& value, const QString& name);
} // namespace QDiscordModel
