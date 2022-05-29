
// Copyright(c) 2022 by wad(wad@inbox.lv)

#pragma once

#include "QDiscordId.h"
#include "QDiscordModel.h"


class QDiscordStageInstance
	: public QDiscordModelBase<QDiscordStageInstance>
{
	Q_GADGET
public:
	enum class PrivacyLevel : qint8
	{
		PUBLIC     = 1, // The Stage instance is visible publicly. (deprecated)
		GUILD_ONLY = 2, // The Stage instance is visible to only guild members.
		Unknown    = -1
	};
	Q_ENUM(PrivacyLevel)

	static QSharedPointer<QDiscordStageInstance> fromJson(const QJsonObject& object);
	QDiscordStageInstance(const QJsonObject& object);
	QDiscordStageInstance() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._id, "id");
		field(a, self._guild_id, "guild_id");
		field(a, self._channel_id, "channel_id");
		field(a, self._topic, "topic");
		field(a, self._privacy_level, "privacy_level");
		field(a, self._discoverable_disabled, "discoverable_disabled");
		field(a, self._guild_scheduled_event_id, "guild_scheduled_event_id");
	}

private:
	QDiscordID                _id;         // The id of this Stage instance
	QDiscordID                _guild_id;   // The guild id of the associated Stage channel
	QDiscordID                _channel_id; // The id of the associated Stage channel
	QString                   _topic;      // The topic of the Stage instance (1-120 characters)
	PrivacyLevel              _privacy_level = PrivacyLevel::Unknown; // The privacy level of the Stage instance
	bool                      _discoverable_disabled = false; // Whether or not Stage Discovery is disabled (deprecated)
	std::optional<QDiscordID> _guild_scheduled_event_id; // The id of the scheduled event for this Stage instance
};
Q_DECLARE_METATYPE(QDiscordStageInstance)


namespace QDiscordModel
{
template<>
void field(QDiscordModel::DeserializeJsonAction& action, QDiscordStageInstance::PrivacyLevel& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QDiscordStageInstance::PrivacyLevel& value, const QString& name);
} // namespace QDiscordModel

