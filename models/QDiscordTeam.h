
// Copyright(c) 2022 by wad(wad@inbox.lv)

#pragma once

#include "QDiscordModel.h"
#include "QDiscordId.h"
#include "QDiscordUser.h"


class QDiscordTeamMember
	: public QDiscordModelBase<QDiscordTeamMember>
{
	Q_GADGET
public:
	enum class MembershipState : qint8
	{
		INVITED = 1,
		ACCEPTED = 2,
		Unknown = -1
	};
	Q_ENUM(MembershipState)

	static QSharedPointer<QDiscordTeamMember> fromJson(const QJsonObject& object);
	QDiscordTeamMember(const QJsonObject& object);
	QDiscordTeamMember() = default;
	void deserialize(const QJsonObject & object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._membership_state, "membership_state");
		field(a, self._permissions, "permissions");
		field(a, self._team_id, "team_id");
		field(a, self._user, "user");
	}

private:
	MembershipState _membership_state = MembershipState::Unknown; // the user's membership state on the team
	QList<QString>  _permissions; // will always be ["*"]
	QDiscordID      _team_id; // the id of the parent team of which they are a member
	QDiscordUser    _user; // partial user object. the avatar, discriminator, id, and username of the user
};
Q_DECLARE_METATYPE(QDiscordTeamMember)


class QDiscordTeam
	: public QDiscordModelBase<QDiscordTeam>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordTeam> fromJson(const QJsonObject& object);
	QDiscordTeam(const QJsonObject& object);
	QDiscordTeam() = default;
	void deserialize(const QJsonObject & object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._icon, "icon");
		field(a, self._id, "id");
		field(a, self._members, "members");
		field(a, self._name, "name");
		field(a, self._owner_user_id, "owner_user_id");
	}

private:
	std::optional<QString>    _icon; // a hash of the image of the team's icon
	QDiscordID                _id; // the unique id of the team
	QList<QDiscordTeamMember> _members; // the members of the team
	QString                   _name; // the name of the team
	QDiscordID                _owner_user_id; // the user id of the current team owner
};
Q_DECLARE_METATYPE(QDiscordTeam)


namespace QDiscordModel
{
template<>
void field(QDiscordModel::DeserializeJsonAction& action, QDiscordTeamMember::MembershipState& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QDiscordTeamMember::MembershipState& value, const QString& name);
}; // namespace QDiscordModel

