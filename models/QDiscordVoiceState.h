
// Copyright(c) 2022 by wad(wad@inbox.lv)

#pragma once

#include "QDiscordId.h"
#include "QDiscordModel.h"
#include "QDiscordMember.h"


class QDiscordVoiceState
	: public QDiscordModelBase<QDiscordVoiceState>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordVoiceState> fromJson(const QJsonObject& object);
	QDiscordVoiceState(const QJsonObject& object);
	QDiscordVoiceState() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._guild_id, "guild_id");
		field(a, self._channel_id, "channel_id");
		field(a, self._user_id, "user_id");
		field(a, self._member, "member");
		field(a, self._session_id, "session_id");
		field(a, self._deaf, "deaf");
		field(a, self._mute, "mute");
		field(a, self._self_deaf, "self_deaf");
		field(a, self._self_mute, "self_mute");
		field(a, self._self_stream, "self_stream");
		field(a, self._self_video, "self_video");
		field(a, self._suppress, "suppress");
		field(a, self._request_to_speak_timestamp, "request_to_speak_timestamp");
	}

private:
	std::optional<QDiscordID>     _guild_id;                   // the guild id this voice state is for
	std::optional<QDiscordID>     _channel_id;                 // the channel id this user is connected to
	std::optional<QDiscordID>     _user_id;                    // the user id this voice state is for
	std::optional<QDiscordMember> _member;                     // the guild member this voice state is for
	QString                       _session_id;                 // the session id for this voice state
	bool                          _deaf = false;               // whether this user is deafened by the server
	bool                          _mute = false;               // whether this user is muted by the server
	bool                          _self_deaf = false;          // whether this user is locally deafened
	bool                          _self_mute = false;          // whether this user is locally muted
	std::optional<bool>           _self_stream;                // whether this user is streaming using "Go Live"
	bool                          _self_video = false;         // whether this user's camera is enabled
	bool                          _suppress = false;           // whether this user is muted by the current user
	std::optional<QDateTime>      _request_to_speak_timestamp; // the time at which the user requested to speak
};
Q_DECLARE_METATYPE(QDiscordVoiceState)


class QDiscordVoiceRegion
	: public QDiscordModelBase<QDiscordVoiceRegion>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordVoiceRegion> fromJson(const QJsonObject& object);
	QDiscordVoiceRegion(const QJsonObject& object);
	QDiscordVoiceRegion() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._id, "id");
		field(a, self._name, "name");
		field(a, self._optimal, "optimal");
		field(a, self._deprecated, "deprecated");
		field(a, self._custom, "custom");
	}

private:
	QString _id;                 // unique ID for the region
	QString _name;               // name of the region
	bool    _optimal = false;    // true for a single server that is closest to the current user's client
	bool    _deprecated = false; // whether this is a deprecated voice region (avoid switching to these)
	bool    _custom = false;     // whether this is a custom voice region (used for events/etc)
};
Q_DECLARE_METATYPE(QDiscordVoiceRegion)


