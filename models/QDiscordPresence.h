
// Copyright(c) 2022 by wad(wad@inbox.lv)

#pragma once

#include "QDiscordId.h"
#include "QDiscordModel.h"
#include "QDiscordUser.h"


class QDiscordClientStatus
	: public QDiscordModelBase<QDiscordClientStatus>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordClientStatus> fromJson(const QJsonObject& object);
	QDiscordClientStatus(const QJsonObject& object);
	QDiscordClientStatus() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._desktop, "desktop");
		field(a, self._mobile, "mobile");
		field(a, self._web, "web");
	}

private:
	std::optional<QString> _desktop; // the user's status set for an active desktop (Windows, Linux, Mac) application session
	std::optional<QString> _mobile;  // the user's status set for an active mobile (iOS, Android) application session
	std::optional<QString> _web;     // the user's status set for an active web (browser, bot account) application session
};
Q_DECLARE_METATYPE(QDiscordClientStatus)


class QDiscordActivityTimestamps
	: public QDiscordModelBase<QDiscordActivityTimestamps>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordActivityTimestamps> fromJson(const QJsonObject& object);
	QDiscordActivityTimestamps(const QJsonObject& object);
	QDiscordActivityTimestamps() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._start, "start");
		field(a, self._end, "end");
	}

private:
	std::optional<int> _start; // unix time (in milliseconds) of when the activity started
	std::optional<int> _end;   // unix time (in milliseconds) of when the activity ends
};
Q_DECLARE_METATYPE(QDiscordActivityTimestamps)


class QDiscordActivityEmoji
	: public QDiscordModelBase<QDiscordActivityEmoji>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordActivityEmoji> fromJson(const QJsonObject& object);
	QDiscordActivityEmoji(const QJsonObject& object);
	QDiscordActivityEmoji() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._name, "name");
		field(a, self._id, "id");
		field(a, self._animated, "animated");
	}

private:
	QString                   _name;     // the name of the emoji
	std::optional<QDiscordID> _id;       // the id of the emoji
	std::optional<bool>       _animated; // whether this emoji is animated
};
Q_DECLARE_METATYPE(QDiscordActivityEmoji)


class QDiscordActivityParty
	: public QDiscordModelBase<QDiscordActivityParty>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordActivityParty> fromJson(const QJsonObject& object);
	QDiscordActivityParty(const QJsonObject& object);
	QDiscordActivityParty() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._id, "id");
		field(a, self._size, "size");
	}

private:
	std::optional<QString>         _id;   // the id of the party
	std::optional<QPair<int, int>> _size; // array of two integers (current_size, max_size)	used to show the party's current and maximum size
};
Q_DECLARE_METATYPE(QDiscordActivityParty)


class QDiscordActivityAssets
	: public QDiscordModelBase<QDiscordActivityAssets>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordActivityAssets> fromJson(const QJsonObject& object);
	QDiscordActivityAssets(const QJsonObject& object);
	QDiscordActivityAssets() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._large_image, "large_image");
		field(a, self._large_text, "large_text");
		field(a, self._small_image, "small_image");
		field(a, self._small_text, "small_text");
	}

private:
	std::optional<QString> _large_image; // see Activity Asset Image
	std::optional<QString> _large_text;  // text displayed when hovering over the large image of the activity
	std::optional<QString> _small_image; // see Activity Asset Image
	std::optional<QString> _small_text;  // text displayed when hovering over the small image of the activity
};
Q_DECLARE_METATYPE(QDiscordActivityAssets)


class QDiscordActivitySecrets
	: public QDiscordModelBase<QDiscordActivitySecrets>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordActivitySecrets> fromJson(const QJsonObject& object);
	QDiscordActivitySecrets(const QJsonObject& object);
	QDiscordActivitySecrets() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._join, "join");
		field(a, self._spectate, "spectate");
		field(a, self._match, "match");
	}

private:
	std::optional<QString> _join;     // the secret for joining a party
	std::optional<QString> _spectate; // the secret for spectating a game
	std::optional<QString> _match;    // the secret for a specific instanced match
};
Q_DECLARE_METATYPE(QDiscordActivitySecrets)


class QDiscordActivityButtons
	: public QDiscordModelBase<QDiscordActivityButtons>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordActivityButtons> fromJson(const QJsonObject& object);
	QDiscordActivityButtons(const QJsonObject& object);
	QDiscordActivityButtons() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._label, "label");
		field(a, self._url, "url");
	}

private:
	QString _label; // the text shown on the button (1-32 characters)
	QString _url;   // the url opened when clicking the button (1-512 characters)
};
Q_DECLARE_METATYPE(QDiscordActivityButtons)


class QDiscordActivity
	: public QDiscordModelBase<QDiscordActivity>
{
	Q_GADGET
public:
	enum class ActivityType : qint8
	{
		Game      = 0, // Playing{ name }	"Playing Rocket League"
		Streaming = 1, // Streaming{ details }	"Streaming Rocket League"
		Listening = 2, // Listening to{ name }	"Listening to Spotify"
		Watching  = 3, // Watching{ name }	"Watching YouTube Together"
		Custom    = 4, // { emoji } {name}	":smiley: I am cool"
		Competing = 5, // Competing in{ name }	"Competing in Arena World Champions"
		Unknown   = -1
	};
	Q_ENUM(ActivityType)

	enum class ActivityFlags : quint16
	{
		INSTANCE                    = 1 << 0,
		JOIN                        = 1 << 1,
		SPECTATE                    = 1 << 2,
		JOIN_REQUEST                = 1 << 3,
		SYNC                        = 1 << 4,
		PLAY                        = 1 << 5,
		PARTY_PRIVACY_FRIENDS       = 1 << 6,
		PARTY_PRIVACY_VOICE_CHANNEL = 1 << 7,
		EMBEDDED                    = 1 << 8
	};

	static QSharedPointer<QDiscordActivity> fromJson(const QJsonObject& object);
	QDiscordActivity(const QJsonObject& object);
	QDiscordActivity() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._name, "name");
		field(a, self._type, "type");
		field(a, self._url, "url");
		field(a, self._created_at, "created_at");
		field(a, self._timestamps, "timestamps");
		field(a, self._application_id, "application_id");
		field(a, self._details, "details");
		field(a, self._state, "state");
		field(a, self._emoji, "emoji");
		field(a, self._party, "party");
		field(a, self._assets, "assets");
		field(a, self._secrets, "secrets");
		field(a, self._instance, "instance");
		field(a, self._flags, "flags");
		field(a, self._buttons, "buttons");
	}

private:
	QString                                   _name;                         // the activity's name
	ActivityType                              _type = ActivityType::Unknown; // activity type
	std::optional<QString>                    _url;                          // stream url, is validated when type is 1
	int                                       _created_at;                   // unix timestamp (in milliseconds) of when the activity was added to the user's session
	std::optional<QDiscordActivityTimestamps> _timestamps;                   // unix timestamps for start and/or end of the game
	std::optional<QDiscordID>                 _application_id;               // application id for the game
	std::optional<QString>                    _details;                      // what the player is currently doing
	std::optional<QString>                    _state;                        // the user's current party status
	std::optional<QDiscordActivityEmoji>      _emoji;                        // the emoji used for a custom status
	std::optional<QDiscordActivityParty>      _party;                        // information for the current party of the player
	std::optional<QDiscordActivityAssets>     _assets;                       // images for the presence and their hover texts
	std::optional<QDiscordActivitySecrets>    _secrets;                      // secrets for Rich Presence joining and spectating
	std::optional<bool>                       _instance;                     // whether or not the activity is an instanced game session
	std::optional<int>                        _flags;                        // activity flags ORd together, describes what the payload includes (ActivityFlags)
	QList<QDiscordActivityButtons>            _buttons;                      // the custom buttons shown in the Rich Presence (max 2)
};
Q_DECLARE_METATYPE(QDiscordActivity)


class QDiscordPresence
	: public QDiscordModelBase<QDiscordPresence>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordPresence> fromJson(const QJsonObject& object);
	QDiscordPresence(const QJsonObject& object);
	QDiscordPresence() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._user, "user");
		field(a, self._guild_id, "guild_id");
		field(a, self._status, "status");
		field(a, self._activities, "activities");
		field(a, self._client_status, "client_status");
	}

private:
	QDiscordUser            _user;          // the user presence is being updated for
	QDiscordID              _guild_id;      // id of the guild
	QString                 _status;        // either "idle", "dnd", "online", or "offline"
	QList<QDiscordActivity> _activities;    // user's current activities
	QDiscordClientStatus    _client_status; // user's platform-dependent status
};
Q_DECLARE_METATYPE(QDiscordPresence)


namespace QDiscordModel
{
template<>
void field(QDiscordModel::DeserializeJsonAction& action, std::optional<std::pair<int, int>>& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const std::optional<std::pair<int, int>>& value, const QString& name);
template<>
void field(QDiscordModel::DeserializeJsonAction& action, QDiscordActivity::ActivityType& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QDiscordActivity::ActivityType& value, const QString& name);
} // namespace QDiscordModel
