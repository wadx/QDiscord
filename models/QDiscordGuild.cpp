/*
 * QDiscord - An unofficial C++ and Qt wrapper for the Discord API.
 * Copyright (C) 2016-2017 george99g
 * Copyright(c) 2022 by wad(wad@inbox.lv)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 */

#include "stdafx.h"
#include "QDiscordGuild.h"
#include "QDiscordChannel.h"
#include "QDiscordRest.h"
#include "updateIfValue.h"


QSharedPointer<QDiscordWelcomeScreenChannel> QDiscordWelcomeScreenChannel::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordWelcomeScreenChannel> out(new QDiscordWelcomeScreenChannel());
	out->deserialize(object);
	return out;
}


QDiscordWelcomeScreenChannel::QDiscordWelcomeScreenChannel(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordWelcomeScreenChannel::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordWelcomeScreenChannel::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordWelcomeScreen> QDiscordWelcomeScreen::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordWelcomeScreen> out(new QDiscordWelcomeScreen());
	out->deserialize(object);
	return out;
}


QDiscordWelcomeScreen::QDiscordWelcomeScreen(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordWelcomeScreen::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordWelcomeScreen::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordGuild> QDiscordGuild::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordGuild> guild(new QDiscordGuild());
	guild->deserialize(object);
	return guild;
}


void QDiscordGuild::listMembers(QDiscordRest& rest, const QDiscordID& guild, uint16_t limit, const QDiscordID& after, const std::function<void(QList<QDiscordMember>)>& callback)
{
	rest.request(QDiscordRoutes::Guilds::listGuildMembers(guild, limit, after), [&rest, callback](QNetworkReply* reply)
	{
		QList<QDiscordMember> memberList;
		if (reply->error() != QNetworkReply::NoError)
		{
			callback(memberList);
			return;
		}
		QJsonArray array = QJsonDocument::fromJson(reply->readAll()).array();
		for (const QJsonValue v : array)
		{
			QDiscordMember member(v.toObject());
			memberList.append(member);
		}
		callback(memberList);
	});
}


QDiscordGuild::QDiscordGuild(const QDiscordGuild& other)
	: QEnableSharedFromThis<QDiscordGuild>(other)
	, _id(other._id)
	, _unavailable(other._unavailable)
	, _name(other._name)
	, _icon(other._icon)
	, _splash(other._splash)
	, _ownerId(other._ownerId)
	, _region(other._region)
	, _afkChannelId(other._afkChannelId)
	, _verificationLevel(other._verificationLevel)
	, _afkTimeout(other._afkTimeout)
	, _defaultMessageNotifications(other._defaultMessageNotifications)
	, _explicitContentFilter(other._explicitContentFilter)
	, _features(other._features)
	, _mfaLevel(other._mfaLevel)
	, _memberCount(other._memberCount)
	, _applicationId(other._applicationId)
{
	for (const QSharedPointer<QDiscordRole>& item : other.roles())
	{
		QSharedPointer<QDiscordRole> newRole(new QDiscordRole(*item));
		newRole->setGuild(sharedFromThis());
		_roles.insert(newRole->id(), newRole);
	}

	for (const QSharedPointer<QDiscordChannel>& item : other.channels())
	{
		QSharedPointer<QDiscordChannel> newChannel = QSharedPointer<QDiscordChannel>(new QDiscordChannel(*item));
		newChannel->setGuild(sharedFromThis());
		_channels.insert(newChannel->id(), newChannel);
	}

	for (const QSharedPointer<QDiscordMember>& item : other.members())
	{
		QSharedPointer<QDiscordMember> newMember = QSharedPointer<QDiscordMember>(new QDiscordMember(*item));
		newMember->setGuild(sharedFromThis());
		_members.insert(newMember->user()->id(), newMember);
	}
}


void QDiscordGuild::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordGuild::serialize()
{
	return serializeJson();
}


void QDiscordGuild::update(const QDiscordGuild& other)
{
	updateIfValue(_id, other._id);
	updateIfValue(_unavailable, other._unavailable);
	if (_unavailable.has_value() && !_unavailable.value())
	{
		updateIfValue(_name, other._name);
		updateIfValue(_icon, other._icon);
		updateIfValue(_icon_hash, other._icon_hash);
		updateIfValue(_splash, other._splash);
		updateIfValue(_discovery_splash, other._discovery_splash);
		updateIfValue(_owner, other._owner);
		updateIfValue(_ownerId, other._ownerId);
		updateIfValue(_permissions, other._permissions);
		updateIfValue(_region, other._region);
		updateIfValue(_afkChannelId, other._afkChannelId);
		updateIfValue(_afkTimeout, other._afkTimeout);
		updateIfValue(_widget_enabled, other._widget_enabled);
		updateIfValue(_widget_channel_id, other._widget_channel_id);
		updateIfValue(_verificationLevel, other._verificationLevel);
		updateIfValue(_defaultMessageNotifications, other._defaultMessageNotifications);
		updateIfValue(_explicitContentFilter, other._explicitContentFilter);
		updateIfValue(_roles, other._roles);
		updateIfValue(_emojis, other._emojis);
		updateIfValue(_features, other._features);
		updateIfValue(_mfaLevel, other._mfaLevel);
		updateIfValue(_applicationId, other._applicationId);
		updateIfValue(_system_channel_id, other._system_channel_id);
		updateIfValue(_system_channel_flags, other._system_channel_flags);
		updateIfValue(_rules_channel_id, other._rules_channel_id);
		updateIfValue(_max_presences, other._max_presences);
		updateIfValue(_max_members, other._max_members);
		updateIfValue(_vanity_url_code, other._vanity_url_code);
		updateIfValue(_description, other._description);
		updateIfValue(_premium_tier, other._premium_tier);
		updateIfValue(_premium_subscription_count, other._premium_subscription_count);
		updateIfValue(_preferred_locale, other._preferred_locale);
		updateIfValue(_public_updates_channel_id, other._public_updates_channel_id);
		updateIfValue(_max_video_channel_users, other._max_video_channel_users);
		updateIfValue(_approximate_member_count, other._approximate_member_count);
		updateIfValue(_approximate_presence_count, other._approximate_presence_count);
		updateIfValue(_welcome_screen, other._welcome_screen);
		updateIfValue(_nsfw_level, other._nsfw_level);
		updateIfValue(_stickers, other._stickers);
		_premium_progress_bar_enabled = other._premium_progress_bar_enabled;
		updateIfValue(_memberCount, other._memberCount);
		updateIfValue(_voice_states, other._voice_states);
		updateIfValue(_members, other._members);
		updateIfValue(_channels, other._channels);
		updateIfValue(_threads, other._threads);
		updateIfValue(_presences, other._presences);
		updateIfValue(_banner, other._banner);
		updateIfValue(_stage_instances, other._stage_instances);
		updateIfValue(_guild_scheduled_events, other._guild_scheduled_events);
	}
}


void QDiscordGuild::addRole(const QSharedPointer<QDiscordRole>& role)
{
	if (!role)
	{
		return;
	}
	_roles.insert(role->id(), role);
}


bool QDiscordGuild::removeRole(const QSharedPointer<QDiscordRole>& role)
{
	if (!role)
	{
		return false;
	}
	return _roles.remove(role->id());
}


bool QDiscordGuild::removeRole(QDiscordID role)
{
	return _roles.remove(role);
}


void QDiscordGuild::addChannel(const QSharedPointer<QDiscordChannel>& channel)
{
	if (!channel)
	{
		return;
	}
	_channels.insert(channel->id(), channel);
}


bool QDiscordGuild::removeChannel(const QSharedPointer<QDiscordChannel>& channel)
{
	if (!channel)
	{
		return false;
	}
	return _channels.remove(channel->id());
}


bool QDiscordGuild::removeChannel(const QDiscordID& channel)
{
	return _channels.remove(channel);
}


void QDiscordGuild::addMember(const QSharedPointer<QDiscordMember>& member)
{
	if (!member)
	{
		return;
	}
	_members.insert(member->user()->id(), member);
}


bool QDiscordGuild::removeMember(const QSharedPointer<QDiscordMember>& member)
{
	if (!member)
	{
		return false;
	}
	return _members.remove(member->user()->id());
}


bool QDiscordGuild::removeMember(const QDiscordID& member)
{
	return _members.remove(member);
}


void QDiscordGuild::resolveRelationships()
{
	for (QSharedPointer<QDiscordRole>& role : _roles)
	{
		role->setGuild(sharedFromThis());
	}
	for (QSharedPointer<QDiscordMember>& member : _members)
	{
		member->setGuild(sharedFromThis());
	}
	for (QSharedPointer<QDiscordChannel>& channel : _channels)
	{
		channel->setGuild(sharedFromThis());
		if (channel->parentId().has_value())
		{
			channel->setParent(QDiscordGuild::channel(channel->parentId().value()));
		}
	}
}


void QDiscordGuild::resolveRelationships() const
{
	// There is nothing to do.
}


namespace
{
	QDiscordGuild::VerificationLevel vlFromInt(int i)
	{
		switch (i)
		{
		case 0:
			return QDiscordGuild::VerificationLevel::None;
		case 1:
			return QDiscordGuild::VerificationLevel::Low;
		case 2:
			return QDiscordGuild::VerificationLevel::Medium;
		case 3:
			return QDiscordGuild::VerificationLevel::High;
		default:
			return QDiscordGuild::VerificationLevel::Unknown;
		}
	}

	QDiscordGuild::NotificationLevel dmnFromInt(int i)
	{
		switch (i)
		{
		case 0:
			return QDiscordGuild::NotificationLevel::AllMessages;
		case 1:
			return QDiscordGuild::NotificationLevel::OnlyMentions;
		default:
			return QDiscordGuild::NotificationLevel::Unknown;
		}
	}

	QDiscordGuild::ExplicitContentFilterLevel ecfFromInt(int i)
	{
		switch (i)
		{
		case 0:
			return QDiscordGuild::ExplicitContentFilterLevel::None;
		case 1:
			return QDiscordGuild::ExplicitContentFilterLevel::WithoutRoles;
		case 2:
			return QDiscordGuild::ExplicitContentFilterLevel::All;
		default:
			return QDiscordGuild::ExplicitContentFilterLevel::Unknown;
		}
	}
} // namespace


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, QDiscordGuild::VerificationLevel& value, const QString& name)
{
	value = vlFromInt(action.data()[name].toInt(-1));
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const QDiscordGuild::VerificationLevel& value, const QString& name)
{
	action.data().insert(name, static_cast<qint8>(value));
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, QDiscordGuild::NotificationLevel& value, const QString& name)
{
	value = dmnFromInt(action.data()[name].toInt(-1));
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const QDiscordGuild::NotificationLevel& value, const QString& name)
{
	action.data().insert(name, static_cast<qint8>(value));
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, QDiscordGuild::ExplicitContentFilterLevel& value, const QString& name)
{
	value = ecfFromInt(action.data()[name].toInt(-1));
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const QDiscordGuild::ExplicitContentFilterLevel& value, const QString& name)
{
	action.data().insert(name, static_cast<qint8>(value));
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, QDiscordGuild::NSFWLevel& value, const QString& name)
{
	switch (action.data()[name].toInt(-1))
	{
	case 0:
		value = QDiscordGuild::NSFWLevel::DEFAULT;
		break;
	case 1:
		value = QDiscordGuild::NSFWLevel::EXPLICIT;
		break;
	case 2:
		value = QDiscordGuild::NSFWLevel::SAFE;
		break;
	case 3:
		value = QDiscordGuild::NSFWLevel::AGE_RESTRICTED;
		break;
	default:
		value = QDiscordGuild::NSFWLevel::Unknown;
	}
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const QDiscordGuild::NSFWLevel& value, const QString& name)
{
	action.data().insert(name, static_cast<int>(value));
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, QDiscordGuild::PremiumTier& value, const QString& name)
{
	switch (action.data()[name].toInt(-1))
	{
	case 0:
		value = QDiscordGuild::PremiumTier::NONE;
		break;
	case 1:
		value = QDiscordGuild::PremiumTier::TIER_1;
		break;
	case 2:
		value = QDiscordGuild::PremiumTier::TIER_2;
		break;
	case 3:
		value = QDiscordGuild::PremiumTier::TIER_3;
		break;
	default:
		value = QDiscordGuild::PremiumTier::Unknown;
	}
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const QDiscordGuild::PremiumTier& value, const QString& name)
{
	action.data().insert(name, static_cast<int>(value));
}
