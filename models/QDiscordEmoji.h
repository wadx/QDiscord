
// Copyright(c) 2022 by wad(wad@inbox.lv)

#pragma once

#include "QDiscordModel.h"
#include "QDiscordId.h"
#include "QDiscordUser.h"


class QDiscordEmoji
	: public QDiscordModelBase<QDiscordEmoji>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordEmoji> fromJson(const QJsonObject& object);
	QDiscordEmoji(const QJsonObject& object);
	QDiscordEmoji() = default;
	void deserialize(const QJsonObject & object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._id, "id");
		field(a, self._name, "name");
		field(a, self._roles, "roles");
		field(a, self._user, "user");
		field(a, self._require_colons, "require_colons");
		field(a, self._managed, "managed");
		field(a, self._animated, "animated");
		field(a, self._available, "available");
	}

private:
	QDiscordID                  _id;             // emoji id
	QString                     _name;           // (can be null only in reaction emoji objects) emoji name
	QList<QDiscordID>           _roles;          // array of role object ids, roles allowed to use this emoji
	std::optional<QDiscordUser> _user;           // user that created this emoji
	std::optional<bool>         _require_colons; // whether this emoji must be wrapped in colons
	std::optional<bool>         _managed;        // whether this emoji is managed
	std::optional<bool>         _animated;       // whether this emoji is animated
	std::optional<bool>         _available;      // whether this emoji can be used, may be false due to loss of Server Boosts
};
Q_DECLARE_METATYPE(QDiscordEmoji)


class QDiscordReaction
	: public QDiscordModelBase<QDiscordReaction>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordReaction> fromJson(const QJsonObject& object);
	QDiscordReaction(const QJsonObject& object);
	QDiscordReaction() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._count, "count");
		field(a, self._me, "me");
		field(a, self._emoji, "emoji");
	}

private:
	int           _count = 0;  // times this emoji has been used to react
	bool          _me = false; // whether the current user reacted using this emoji
	QDiscordEmoji _emoji;      // partial emoji object, emoji information
};
Q_DECLARE_METATYPE(QDiscordReaction)


