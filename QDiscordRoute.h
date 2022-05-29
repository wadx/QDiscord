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

#pragma once

/*
 * This code is based off of the following code by FiniteReality:
 * https://github.com/FiniteReality/disccord/blob/master/include/rest/route.hpp
 * https://github.com/FiniteReality/disccord/blob/master/lib/rest/route.cpp
 * And the following code by DV8FromTheWorld:
 * https://github.com/DV8FromTheWorld/JDA/blob/master/src/main/java/net/dv8tion/jda/core/requests/Route.java
 */

#include "models/QDiscordId.h"


class QDiscordRoute
{
public:
	enum class Method
	{
		GET,
		POST,
		PUT,
		DELETE,
		PATCH
	};
	QDiscordRoute(Method method, const QString& url)
	{
		route(method, url);
	}
	template<class TFirst, class... TArgs>
	QDiscordRoute(Method method, QString base, TFirst first, TArgs... args)
	{
		route(method, base, first, args...);
	}
	Method method() const { return _method; }
	QString bucketUrl() const { return _bucketUrl; }
	QUrl fullUrl() const { return _fullUrl; }
	void setQuery(const QUrlQuery& query)
	{
		_fullUrl.setQuery(query);
	}
private:
	template<class TFirst, class... TArgs>
	QString routeString(QString base, TFirst first, TArgs... args)
	{
		int start = base.indexOf('{');
		int len = base.indexOf('}', start) - start + 1;
		return routeString(base.replace(start, len, first), args...);
	}
	QString routeString(QString url)
	{
		return url;
	}
	template<class TFirst, class... TArgs>
	void route(Method method, QString base, TFirst first, TArgs... args)
	{
		int start = base.indexOf('{');
		int len = base.indexOf('}', start) - start + 1;
		QString parameter = base.mid(start, len);
		if (parameter == "{channel}" || parameter == "{guild}" || parameter == "{interaction_id}" || parameter == "{application_id}" || parameter == "{user_id}")
		{
			route(method, base.replace(start, len, first), args...);
		}
		else
		{
			_method = method;
			_bucketUrl = base;
			_fullUrl = routeString(base.replace(start, len, first), args...);
		}
	}
	void route(QDiscordRoute::Method method, const QString& url)
	{
		_method = method;
		_fullUrl = url;
		_bucketUrl = url;
	}

	Method  _method = Method::GET;
	QString _bucketUrl;
	QUrl    _fullUrl;
};

QDebug& operator<<(QDebug& d, const QDiscordRoute& route);


namespace QDiscordRoutes
{
	namespace Self
	{
		QDiscordRoute getSelf();
		QDiscordRoute modifySelf();
		QDiscordRoute getGuilds();
		QDiscordRoute leaveGuild(const QDiscordID& guild);
		QDiscordRoute getPrivateChannels();
		QDiscordRoute createPrivateChannel();
		QDiscordRoute gateway();
		// Client-only
		QDiscordRoute userSettings();
		QDiscordRoute login();
		QDiscordRoute logout();
	} // namespace Self

	namespace Users
	{
		QDiscordRoute getUser(const QDiscordID& user);
	}

	namespace Guilds
	{
		QDiscordRoute getGuild(const QDiscordID& guild);
		QDiscordRoute modifyGuild(const QDiscordID& guild);
		QDiscordRoute createChannel(const QDiscordID& guild);
		QDiscordRoute getChannels(const QDiscordID& guild);
		QDiscordRoute modifyChannels(const QDiscordID& guild);
		QDiscordRoute getGuildMember(const QDiscordID& guild, const QDiscordID& user);
		QDiscordRoute listGuildMembers(const QDiscordID& guild);
		QDiscordRoute listGuildMembers(const QDiscordID& guild, uint16_t limit);
		QDiscordRoute listGuildMembers(const QDiscordID& guild, uint16_t limit, const QDiscordID& after);
		QDiscordRoute listGuildMembers(const QDiscordID& guild, const QDiscordID& after);
		QDiscordRoute getBans(const QDiscordID& guild);
		QDiscordRoute ban(const QDiscordID& guild, const QDiscordID& user);
		QDiscordRoute banWithDelete(const QDiscordID& guild, const QDiscordID& user, int days);
		QDiscordRoute unban(const QDiscordID& guild, const QDiscordID& user);
		QDiscordRoute kickMember(const QDiscordID& guild, const QDiscordID& user);
		QDiscordRoute modifyMember(const QDiscordID& guild, const QDiscordID& user);
		QDiscordRoute modifySelfNick(const QDiscordID& guild);
		QDiscordRoute prunableCount(const QDiscordID& guild, int days);
		QDiscordRoute pruneMembers(const QDiscordID& guild, int days);
		// Client-only
		QDiscordRoute createGuild();
		QDiscordRoute deleteGuild(const QDiscordID& guild);
	} // namespace Guilds

	namespace Emotes
	{
		QDiscordRoute modifyEmote(const QDiscordID& guild, const QDiscordID& emote);
		QDiscordRoute deleteEmote(const QDiscordID& guild, const QDiscordID& emote);
		QDiscordRoute createEmote(const QDiscordID& guild);
	} // namespace Emotes

	namespace Roles
	{
		QDiscordRoute getRoles(const QDiscordID& guild);
		QDiscordRoute createRole(const QDiscordID& guild);
		QDiscordRoute getRole(const QDiscordID& guild, const QDiscordID& role);
		QDiscordRoute modifyRole(const QDiscordID& guild, const QDiscordID& role);
		QDiscordRoute deleteRole(const QDiscordID& guild, const QDiscordID& role);
	} // namespace Roles

	namespace Channels
	{
		QDiscordRoute deleteChannel(const QDiscordID& channel);
		QDiscordRoute modifyChannel(const QDiscordID& channel);
		QDiscordRoute sendTyping(const QDiscordID& channel);
		QDiscordRoute getPermissions(const QDiscordID& channel);
		QDiscordRoute getChannel(const QDiscordID& channel);
		QDiscordRoute getPermissionsOverride(const QDiscordID& channel, const QDiscordID& permissionsOverride);
		QDiscordRoute createPermissionsOverride(const QDiscordID& channel, const QDiscordID& permissionsOverride);
		QDiscordRoute modifyPermissionsOverride(const QDiscordID& channel, const QDiscordID& permissionsOverride);
		QDiscordRoute deletePermissionsOverride(const QDiscordID& channel, const QDiscordID& permissionsOverride);
	} // namespace Channels

	namespace Messages
	{
		QDiscordRoute sendMessage(const QDiscordID& channel);
		QDiscordRoute editMessage(const QDiscordID& channel, const QDiscordID& message);
		QDiscordRoute deleteMessage(const QDiscordID& channel, const QDiscordID& message);
		QDiscordRoute getPinnedMessages(const QDiscordID& channel);
		QDiscordRoute addPinnedMessage(const QDiscordID& channel, const QDiscordID& message);
		QDiscordRoute removePinnedMessage(const QDiscordID& channel, const QDiscordID& message);
		QDiscordRoute addReaction(const QDiscordID& channel, const QDiscordID& message, const QString& reactionCode);
		QDiscordRoute removeReaction(const QDiscordID& channel, const QDiscordID& message, const QString& reactionCode, const QDiscordID& user);
		QDiscordRoute removeAllReactions(const QDiscordID& channel, const QDiscordID& message);
		QDiscordRoute getReactionUsers(const QDiscordID& channel, const QDiscordID& message, const QString& reactionCode, int limit);
		QDiscordRoute getMessageHistory(const QDiscordID& channel, int limit);
		QDiscordRoute getMessageHistoryBefore(const QDiscordID& channel, int limit, const QDiscordID& before);
		QDiscordRoute getMessageHistoryAfter(const QDiscordID& channel, int limit, const QDiscordID& after);
		QDiscordRoute getMessageHistoryAround(const QDiscordID& channel, int limit, const QDiscordID& around);
		QDiscordRoute ackMessage(const QDiscordID& channel, const QDiscordID& message);
		// Bot-only
		QDiscordRoute getMessage(const QDiscordID& channel, const QDiscordID& message);
		QDiscordRoute deleteMessages(const QDiscordID& channel);
	} // namespace Messages

	namespace Invites
	{
		QDiscordRoute getInvite(const QString& code);
		QDiscordRoute deleteInvite(const QString& code);
		QDiscordRoute getGuildInvites(const QDiscordID& guild);
		QDiscordRoute getChannelInvites(const QDiscordID& channel);
		QDiscordRoute createInvite(const QDiscordID& channel);
		// Client-only
		QDiscordRoute acceptInvite(const QString& code);
	} // namespace Invites

	namespace Interactions
	{
		QDiscordRoute createInteractionResponse(const QDiscordID& interaction_id, const QString& interaction_token);
		QDiscordRoute getOriginalInteractionResponse(const QDiscordID& application_id, const QString& interaction_token);
		QDiscordRoute editOriginalInteractionResponse(const QDiscordID& application_id, const QString& interaction_token);
		QDiscordRoute deleteOriginalInteractionResponse(const QDiscordID& application_id, const QString& interaction_token);
		QDiscordRoute createFollowupMessage(const QDiscordID& application_id, const QString& interaction_token);
		QDiscordRoute getFollowupMessage(const QDiscordID& application_id, const QString& interaction_token, const QDiscordID& message_id);
		QDiscordRoute editFollowupMessage(const QDiscordID& application_id, const QString& interaction_token, const QDiscordID& message_id);
		QDiscordRoute deleteFollowupMessage(const QDiscordID& application_id, const QString& interaction_token, const QDiscordID& message_id);
	} // namespace Interaction

	namespace ApplicationCommands
	{
		QDiscordRoute getGlobalCommands(const QDiscordID& application_id);
		QDiscordRoute overwriteGlobalCommands(const QDiscordID& application_id);
		QDiscordRoute getGlobalCommand(const QDiscordID& application_id, const QDiscordID& command_id);
		QDiscordRoute createGlobalCommand(const QDiscordID& application_id);
		QDiscordRoute editGlobalCommand(const QDiscordID& application_id, const QDiscordID& command_id);
		QDiscordRoute deleteGlobalCommand(const QDiscordID& application_id, const QDiscordID& command_id);

		QDiscordRoute getGuildCommands(const QDiscordID& application_id, const QDiscordID& guild_id);
		QDiscordRoute overwriteGuildCommands(const QDiscordID& application_id, const QDiscordID& guild_id);
		QDiscordRoute getGuildCommand(const QDiscordID& application_id, const QDiscordID& guild_id, const QDiscordID& command_id);
		QDiscordRoute createGuildCommand(const QDiscordID& application_id, const QDiscordID& guild_id);
		QDiscordRoute editGuildCommand(const QDiscordID& application_id, const QDiscordID& guild_id, const QDiscordID& command_id);
		QDiscordRoute deleteGuildCommand(const QDiscordID& application_id, const QDiscordID& guild_id, const QDiscordID& command_id);

		QDiscordRoute getGuildCommandsPermissions(const QDiscordID& application_id, const QDiscordID& guild_id);
		QDiscordRoute putGuildCommandsPermissions(const QDiscordID& application_id, const QDiscordID& guild_id);
		QDiscordRoute getGuildCommandPermissions(const QDiscordID& application_id, const QDiscordID& guild_id, const QDiscordID& command_id);
		QDiscordRoute editGuildCommandPermissions(const QDiscordID& application_id, const QDiscordID& guild_id, const QDiscordID& command_id);
	} // ApplicationCommands

	namespace Avatars
	{
		QDiscordRoute getAvatarPng(const QDiscordID& user_id, const QString& avatar_hash);
	}
} // namespace QDiscordRoutes

