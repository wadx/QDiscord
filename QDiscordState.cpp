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
#include "moc_QDiscordState.cpp"
#include "QDiscordState.h"
#include "QDiscordRest.h"


QDiscordState::QDiscordState(QObject* parent)
	: QDiscordAbstractState(parent)
{
}


void QDiscordState::readyReceived(int protocolVersion, QSharedPointer<QDiscordApplication> application, QSharedPointer<QDiscordUser> user)
{
	_protocolVersion = protocolVersion;
	_application = application;
	_user = user;
	emit selfCreated(_application, _user);
}


void QDiscordState::channelCreateReceived(QSharedPointer<QDiscordChannel> channel)
{
	if(channel->type() == QDiscordChannel::Type::DM || channel->type() == QDiscordChannel::Type::GROUP_DM)
	{
		_dmChannels.insert(channel->id(), channel);
	}
	else
	{
		if (channel->guildId().has_value())
		{
			channel->setGuild(guild(channel->guildId().value()));
		}
		if (!channel->guild())
		{
			return;
		}
		channel->guild()->addChannel(channel);
	}
	emit channelCreated(channel);
}


void QDiscordState::channelUpdateReceived(QSharedPointer<QDiscordChannel> channel)
{
	if (channel->guildId().has_value())
	{
		channel->setGuild(guild(channel->guildId().value()));
	}
	if (channel->guild())
	{
		channel->guild()->addChannel(channel);
	}
	emit channelUpdated(channel);
}


void QDiscordState::channelDeleteReceived(QSharedPointer<QDiscordChannel> channel)
{
	if(channel->type() == QDiscordChannel::Type::DM || channel->type() == QDiscordChannel::Type::GROUP_DM)
	{
		_dmChannels.remove(channel->id());
	}
	else
	{
		if (channel->guildId().has_value())
		{
			channel->setGuild(guild(channel->guildId().value()));
		}
		if (channel->guild())
		{
			channel->guild()->removeChannel(channel->id());
		}
	}
	emit channelDeleted(channel);
}


void QDiscordState::guildCreateReceived(QSharedPointer<QDiscordGuild> guild)
{
	_guilds.insert(guild->id(), guild);
	if (!guild->unavailable().has_value() || guild->unavailable().value())
	{
		emit guildCreated(guild);
	}
	else
	{
		emit guildAvailable(guild);
	}
	emit guildsNumberChanged(_guilds.size());
}


void QDiscordState::guildUpdateReceived(QSharedPointer<QDiscordGuild> guild)
{
	QSharedPointer<QDiscordGuild> oldGuild = QDiscordState::guild(guild->id());
	if(oldGuild)
	{
		oldGuild->update(*guild);
		emit guildUpdated(oldGuild);
	}
}


void QDiscordState::guildDeleteReceived(QSharedPointer<QDiscordGuild> guild)
{
	_guilds.remove(guild->id());
	if (guild->unavailable())
	{
		emit guildUnavailable(guild);
	}
	else
	{
		emit guildDeleted(guild);
	}
	emit guildsNumberChanged(_guilds.size());
}


void QDiscordState::guildBanAddReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordState::guildBanRemoveReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordState::guildEmojisUpdateReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordState::guildIntegrationsUpdateReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordState::guildMemberAddReceived(QSharedPointer<QDiscordMember> member, QDiscordID guildId)
{
	member->setGuild(guild(guildId));
	if (!member->guild())
	{
		return;
	}
	member->guild()->addMember(member);
	emit guildMemberAdded(member);
}


void QDiscordState::guildMemberRemoveReceived(QSharedPointer<QDiscordMember> member, QDiscordID guildId)
{
	member->setGuild(guild(guildId));
	if (!member->guild())
	{
		return;
	}
	QSharedPointer<QDiscordMember> oldMember = member->guild()->member(member->user()->id());
	if (!oldMember)
	{
		return;
	}
	member->guild()->removeMember(member->user()->id());
	emit guildMemberRemoved(oldMember);
}


void QDiscordState::guildMemberUpdateReceived(QSharedPointer<QDiscordMember> member, QDiscordID guildId)
{
	member->setGuild(guild(guildId));
	if (!member->guild())
	{
		return;
	}
	QSharedPointer<QDiscordMember> oldMember = member->guild()->member(member->user()->id());
	if (!oldMember)
	{
		return;
	}
	oldMember->update(*member);
	emit guildMemberUpdated(oldMember);
}


void QDiscordState::guildMembersChunkReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordState::guildRoleCreateReceived(QSharedPointer<QDiscordRole> role, QDiscordID guildId)
{
	role->setGuild(guild(guildId));
	if (!role->guild())
	{
		return;
	}
	role->guild()->addRole(role);
	emit guildRoleCreated(role);
}


void QDiscordState::guildRoleUpdateReceived(QSharedPointer<QDiscordRole> role, QDiscordID guildId)
{
	role->setGuild(guild(guildId));
	if (!role->guild())
	{
		return;
	}
	role->guild()->addRole(role);
	emit guildRoleUpdated(role);
}


void QDiscordState::guildRoleDeleteReceived(QDiscordID roleId, QDiscordID guildId)
{
	QSharedPointer<QDiscordGuild> guild = QDiscordState::guild(guildId);
	if (!guild)
	{
		return;
	}
	QSharedPointer<QDiscordRole> role = guild->role(roleId);
	if (!role)
	{
		return;
	}
	guild->removeRole(role);
	emit guildRoleDeleted(role);
}


void QDiscordState::interactionCreateReceived(QSharedPointer<QDiscordInteraction> interaction)
{
	if (interaction->channel_id().has_value())
	{
		interaction->setChannel(channel(interaction->channel_id().value()));
	}
	emit interactionReceived(interaction);
}


void QDiscordState::messageCreateReceived(QSharedPointer<QDiscordMessage> message)
{
	message->setChannel(channel(message->channelId()));
	emit messageCreated(message);
}


void QDiscordState::messageUpdateReceived(QSharedPointer<QDiscordMessage> message)
{
	message->setChannel(channel(message->channelId()));
	emit messageUpdated(message);
}


void QDiscordState::messageDeleteReceived(QSharedPointer<QDiscordMessage> message)
{
	message->setChannel(channel(message->channelId()));
	emit messageDeleted(message);
}


void QDiscordState::messageDeleteBulkReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordState::presenceUpdateReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordState::typingStartReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordState::userUpdateReceived(QSharedPointer<QDiscordUser> user)
{
	_user = user;
	emit selfUpdated(user);
}


void QDiscordState::applicationCommandPermissionsUpdateReceived(QSharedPointer<QDiscordGuildApplicationCommandPermissions> permissions)
{
	Q_UNUSED(permissions);
	// TODO: Implement this
}


void QDiscordState::voiceStateUpdateReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordState::voiceServerUpdateReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordState::reset()
{
	_protocolVersion = -1;
	_user = QSharedPointer<QDiscordUser>();
	_dmChannels.clear();
	_guilds.clear();
	emit guildsNumberChanged(_guilds.size());
}


QSharedPointer<QDiscordChannel> QDiscordState::channel(const QDiscordID& id) const
{
	QSharedPointer<QDiscordChannel> channel;
	if ((channel = dmChannel(id)))
	{
		return channel;
	}
	for(const QSharedPointer<QDiscordGuild>& guild : _guilds)
	{
		if ((channel = guild->channel(id)))
		{
			return channel;
		}
	}
	return nullptr;
}


