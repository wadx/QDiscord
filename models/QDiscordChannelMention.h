
// Copyright(c) 2022 by wad(wad@inbox.lv)

#pragma once

#include "QDiscordModel.h"
#include "QDiscordId.h"
#include "QDiscordChannel.h"


class QDiscordChannelMention
	: public QDiscordModelBase<QDiscordChannelMention>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordChannelMention> fromJson(const QJsonObject& object);
	QDiscordChannelMention(const QJsonObject& object);
	QDiscordChannelMention() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._id, "id");
		field(a, self._guild_id, "guild_id");
		field(a, self._type, "type");
		field(a, self._name, "name");
	}

private:
	QDiscordID            _id;                                        // id of the channel
	QDiscordID            _guild_id;                                  // id of the guild containing the channel
	QDiscordChannel::Type _type = QDiscordChannel::Type::UnknownType; // the type of channel
	QString               _name;                                      // the name of the channel
};
Q_DECLARE_METATYPE(QDiscordChannelMention)


class QDiscordAllowedMentions
	: public QDiscordModelBase<QDiscordAllowedMentions>
{
	Q_GADGET
public:
	enum class AllowedMentionType : qint8
	{
		RoleMentions,     // "roles"	Controls role mentions
		UserMentions,     // "users"	Controls user mentions
		EveryoneMentions, // "everyone"	Controls @everyone and @here mentions
		Unknown
	};
	Q_ENUM(AllowedMentionType)

	static QSharedPointer<QDiscordAllowedMentions> fromJson(const QJsonObject& object);
	QDiscordAllowedMentions(const QJsonObject& object);
	QDiscordAllowedMentions() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._parse, "parse");
		field(a, self._roles, "roles");
		field(a, self._users, "users");
		field(a, self._replied_user, "replied_user");
	}

private:
	QList<AllowedMentionType> _parse; // An array of allowed mention types to parse from the content.
	QList<QDiscordID>         _roles; // Array of role_ids to mention (Max size of 100)
	QList<QDiscordID>         _users; // Array of user_ids to mention (Max size of 100)
	bool                      _replied_user = false; // For replies, whether to mention the author of the message being replied to (default false)
};
Q_DECLARE_METATYPE(QDiscordAllowedMentions)


namespace QDiscordModel
{
template<>
void field(QDiscordModel::DeserializeJsonAction& action, QList<QDiscordAllowedMentions::AllowedMentionType>& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QList<QDiscordAllowedMentions::AllowedMentionType>& value, const QString& name);
}; // namespace QDiscordModel


