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
#include "QDiscordRoute.h"


QDiscordRoute QDiscordRoutes::Self::getSelf()
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.me);
}


QDiscordRoute QDiscordRoutes::Self::modifySelf()
{
	return QDiscordRoute(QDiscordRoute::Method::PATCH, QDiscordUtilities::endPoints.me);
}


QDiscordRoute QDiscordRoutes::Self::getGuilds()
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.me + "/guilds");
}


QDiscordRoute QDiscordRoutes::Self::leaveGuild(const QDiscordID& guild)
{
	return QDiscordRoute(QDiscordRoute::Method::DELETE, QDiscordUtilities::endPoints.me + "/guilds/{guildm}", guild.toString());
}


QDiscordRoute QDiscordRoutes::Self::getPrivateChannels()
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.me + "/channels");
}


QDiscordRoute QDiscordRoutes::Self::createPrivateChannel()
{
	return QDiscordRoute(QDiscordRoute::Method::POST, QDiscordUtilities::endPoints.me + "/channels");
}


QDiscordRoute QDiscordRoutes::Self::gateway()
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.gateway);
}


QDiscordRoute QDiscordRoutes::Self::userSettings()
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.me + "/settings");
}


QDiscordRoute QDiscordRoutes::Self::login()
{
	return QDiscordRoute(QDiscordRoute::Method::POST, QDiscordUtilities::endPoints.login);
}


QDiscordRoute QDiscordRoutes::Self::logout()
{
	return QDiscordRoute(QDiscordRoute::Method::POST, QDiscordUtilities::endPoints.logout);
}


// Users
QDiscordRoute QDiscordRoutes::Users::getUser(const QDiscordID& user)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.users + "/{user}", user.toString());
}


// Guilds
QDiscordRoute QDiscordRoutes::Guilds::getGuild(const QDiscordID& guild)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.guilds + "/{guild}", guild.toString());
}


QDiscordRoute QDiscordRoutes::Guilds::modifyGuild(const QDiscordID& guild)
{
	return QDiscordRoute(QDiscordRoute::Method::PATCH, QDiscordUtilities::endPoints.guilds + "/{guild}", guild.toString());
}


QDiscordRoute QDiscordRoutes::Guilds::createChannel(const QDiscordID& guild)
{
	return QDiscordRoute(QDiscordRoute::Method::POST, QDiscordUtilities::endPoints.guilds + "/{guild}/channels", guild.toString());
}


QDiscordRoute QDiscordRoutes::Guilds::getChannels(const QDiscordID& guild)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.guilds + "/{guild}/channels", guild.toString());
}


QDiscordRoute QDiscordRoutes::Guilds::modifyChannels(const QDiscordID& guild)
{
	return QDiscordRoute(QDiscordRoute::Method::PATCH, QDiscordUtilities::endPoints.guilds + "/{guild}/channels", guild.toString());
}


QDiscordRoute QDiscordRoutes::Guilds::getGuildMember(const QDiscordID& guild, const QDiscordID& user)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.guilds + "/{guild}/members/{user}", guild.toString(), user.toString());
}


QDiscordRoute QDiscordRoutes::Guilds::listGuildMembers(const QDiscordID& guild)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.guilds + "/{guild}/members", guild.toString());
}


QDiscordRoute QDiscordRoutes::Guilds::listGuildMembers(const QDiscordID& guild, uint16_t limit)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.guilds + "/{guild}/members?limit={limit}", guild.toString(), QString::number(limit));
}


QDiscordRoute QDiscordRoutes::Guilds::listGuildMembers(const QDiscordID& guild, uint16_t limit, const QDiscordID& after)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.guilds + "/{guild}/members?limit={limit}&after={after}", guild.toString(), QString::number(limit), after.toString());
}


QDiscordRoute QDiscordRoutes::Guilds::listGuildMembers(const QDiscordID& guild, const QDiscordID& after)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.guilds + "/{guild}/members?after={after}", guild.toString(), after.toString());
}


QDiscordRoute QDiscordRoutes::Guilds::getBans(const QDiscordID& guild)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.guilds + "/{guild}/bans", guild.toString());
}


QDiscordRoute QDiscordRoutes::Guilds::ban(const QDiscordID& guild, const QDiscordID& user)
{
	return QDiscordRoute(QDiscordRoute::Method::PUT, QDiscordUtilities::endPoints.guilds + "/{guild}/bans/{user}", guild.toString(), user.toString());
}


QDiscordRoute QDiscordRoutes::Guilds::banWithDelete(const QDiscordID& guild, const QDiscordID& user, int days)
{
	return QDiscordRoute(QDiscordRoute::Method::PUT, QDiscordUtilities::endPoints.guilds + "/{guild}/bans/{user}?delete-message-days={days}", guild.toString(), user.toString(), QString::number(days));
}


QDiscordRoute QDiscordRoutes::Guilds::unban(const QDiscordID& guild, const QDiscordID& user)
{
	return QDiscordRoute(QDiscordRoute::Method::DELETE, QDiscordUtilities::endPoints.guilds + "/{guild}/bans/{user}", guild.toString(), user.toString());
}


QDiscordRoute QDiscordRoutes::Guilds::kickMember(const QDiscordID& guild, const QDiscordID& user)
{
	return QDiscordRoute(QDiscordRoute::Method::DELETE, QDiscordUtilities::endPoints.guilds + "/{guild}/members/{user}", guild.toString(), user.toString());
}


QDiscordRoute QDiscordRoutes::Guilds::modifyMember(const QDiscordID& guild, const QDiscordID& user)
{
	return QDiscordRoute(QDiscordRoute::Method::PATCH, QDiscordUtilities::endPoints.guilds + "/{guild}/members/{user}", guild.toString(), user.toString());
}


QDiscordRoute QDiscordRoutes::Guilds::modifySelfNick(const QDiscordID& guild)
{
	return QDiscordRoute(QDiscordRoute::Method::PATCH, QDiscordUtilities::endPoints.guilds + "/{guild}/@me/nick", guild.toString());
}


QDiscordRoute QDiscordRoutes::Guilds::prunableCount(const QDiscordID& guild, int days)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.guilds + "/{guild}/prune?days={days}", guild.toString(), QString::number(days));
}


QDiscordRoute QDiscordRoutes::Guilds::pruneMembers(const QDiscordID& guild, int days)
{
	return QDiscordRoute(QDiscordRoute::Method::POST, QDiscordUtilities::endPoints.guilds + "/{guild}/prune?days={days}", guild.toString(), QString::number(days));
}


QDiscordRoute QDiscordRoutes::Guilds::createGuild()
{
	return QDiscordRoute(QDiscordRoute::Method::POST, QDiscordUtilities::endPoints.guilds);
}


QDiscordRoute QDiscordRoutes::Guilds::deleteGuild(const QDiscordID& guild)
{
	return QDiscordRoute(QDiscordRoute::Method::POST, QDiscordUtilities::endPoints.guilds + "/{guildm}/delete", guild.toString());
}


// Emotes
QDiscordRoute QDiscordRoutes::Emotes::modifyEmote(const QDiscordID& guild, const QDiscordID& emote)
{
	return QDiscordRoute(QDiscordRoute::Method::PATCH, QDiscordUtilities::endPoints.guilds + "/{guildm}/emojis/{emote}", guild.toString(), emote.toString());
}


QDiscordRoute QDiscordRoutes::Emotes::deleteEmote(const QDiscordID& guild, const QDiscordID& emote)
{
	return QDiscordRoute(QDiscordRoute::Method::DELETE, QDiscordUtilities::endPoints.guilds + "/{guildm}/emojis/{emote}", guild.toString(), emote.toString());
}


QDiscordRoute QDiscordRoutes::Emotes::createEmote(const QDiscordID& guild)
{
	return QDiscordRoute(QDiscordRoute::Method::POST, QDiscordUtilities::endPoints.guilds + "/{guildm}/emojis", guild.toString());
}


// Roles
QDiscordRoute QDiscordRoutes::Roles::getRoles(const QDiscordID& guild)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.guilds + "/{guild}/roles", guild.toString());
}


QDiscordRoute QDiscordRoutes::Roles::createRole(const QDiscordID& guild)
{
	return QDiscordRoute(QDiscordRoute::Method::POST, QDiscordUtilities::endPoints.guilds + "/{guild}/roles", guild.toString());
}


QDiscordRoute QDiscordRoutes::Roles::getRole(const QDiscordID& guild, const QDiscordID& role)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.guilds + "/{guild}/roles/{role}", guild.toString(), role.toString());
}


QDiscordRoute QDiscordRoutes::Roles::modifyRole(const QDiscordID& guild, const QDiscordID& role)
{
	return QDiscordRoute(QDiscordRoute::Method::PATCH, QDiscordUtilities::endPoints.guilds + "/{guild}/roles/{role}", guild.toString(), role.toString());
}


QDiscordRoute QDiscordRoutes::Roles::deleteRole(const QDiscordID& guild, const QDiscordID& role)
{
	return QDiscordRoute(QDiscordRoute::Method::DELETE, QDiscordUtilities::endPoints.guilds + "/{guild}/roles/{role}", guild.toString(), role.toString());
}


// Channels
QDiscordRoute QDiscordRoutes::Channels::deleteChannel(const QDiscordID& channel)
{
	return QDiscordRoute(QDiscordRoute::Method::DELETE, QDiscordUtilities::endPoints.channels + "/{channelm}", channel.toString());
}


QDiscordRoute QDiscordRoutes::Channels::modifyChannel(const QDiscordID& channel)
{
	return QDiscordRoute(QDiscordRoute::Method::PATCH, QDiscordUtilities::endPoints.channels + "/{channel}", channel.toString());
}


QDiscordRoute QDiscordRoutes::Channels::sendTyping(const QDiscordID& channel)
{
	return QDiscordRoute(QDiscordRoute::Method::POST, QDiscordUtilities::endPoints.channels + "/{channel}/typing", channel.toString());
}


QDiscordRoute QDiscordRoutes::Channels::getChannel(const QDiscordID& channel)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.channels + "/{channel}", channel.toString());
}


QDiscordRoute QDiscordRoutes::Channels::getPermissions(const QDiscordID& channel)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.channels + "/{channel}/permissions", channel.toString());
}


QDiscordRoute QDiscordRoutes::Channels::getPermissionsOverride(const QDiscordID& channel, const QDiscordID& permissionsOverride)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.channels + "/{channel}/permissions/{permoverride}", channel.toString(), permissionsOverride.toString());
}


QDiscordRoute QDiscordRoutes::Channels::createPermissionsOverride(const QDiscordID& channel, const QDiscordID& permissionsOverride)
{
	return QDiscordRoute(QDiscordRoute::Method::PUT, QDiscordUtilities::endPoints.channels + "/{channel}/permissions/{permoverride}", channel.toString(), permissionsOverride.toString());
}


QDiscordRoute QDiscordRoutes::Channels::modifyPermissionsOverride(const QDiscordID& channel, const QDiscordID& permissionsOverride)
{
	return QDiscordRoute(QDiscordRoute::Method::PUT, QDiscordUtilities::endPoints.channels + "/{channel}/permissions/{permoverride}", channel.toString(), permissionsOverride.toString());
}


QDiscordRoute QDiscordRoutes::Channels::deletePermissionsOverride(const QDiscordID& channel, const QDiscordID& permissionsOverride)
{
	return QDiscordRoute(QDiscordRoute::Method::DELETE, QDiscordUtilities::endPoints.channels + "/{channel}/permissions/{permoverride}", channel.toString(), permissionsOverride.toString());
}


// Messages
QDiscordRoute QDiscordRoutes::Messages::sendMessage(const QDiscordID& channel)
{
	return QDiscordRoute(QDiscordRoute::Method::POST, QDiscordUtilities::endPoints.channels + "/{channel}/messages", channel.toString());
}


QDiscordRoute QDiscordRoutes::Messages::editMessage(const QDiscordID& channel, const QDiscordID& message)
{
	return QDiscordRoute(QDiscordRoute::Method::PATCH, QDiscordUtilities::endPoints.channels + "/{channel}/messages/{message}", channel.toString(), message.toString());
}


QDiscordRoute QDiscordRoutes::Messages::deleteMessage(const QDiscordID& channel, const QDiscordID& message)
{
	return QDiscordRoute(QDiscordRoute::Method::DELETE, QDiscordUtilities::endPoints.channels + "/{channel}/messages/{message}", channel.toString(), message.toString());
}


QDiscordRoute QDiscordRoutes::Messages::getPinnedMessages(const QDiscordID& channel)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.channels + "/{channel}/pins", channel.toString());
}


QDiscordRoute QDiscordRoutes::Messages::addPinnedMessage(const QDiscordID& channel, const QDiscordID& message)
{
	return QDiscordRoute(QDiscordRoute::Method::PUT, QDiscordUtilities::endPoints.channels + "/{channel}/pins/{message}", channel.toString(), message.toString());
}


QDiscordRoute QDiscordRoutes::Messages::removePinnedMessage(const QDiscordID& channel, const QDiscordID& message)
{
	return QDiscordRoute(QDiscordRoute::Method::DELETE, QDiscordUtilities::endPoints.channels + "/{channel}/pins/{message}", channel.toString(), message.toString());
}


QDiscordRoute QDiscordRoutes::Messages::addReaction(const QDiscordID& channel, const QDiscordID& message, const QString& reactionCode)
{
	return QDiscordRoute(QDiscordRoute::Method::PUT, QDiscordUtilities::endPoints.channels + "/{channel}/messages/{message}/reactions/{reaction}/@me", channel.toString(), message.toString(), reactionCode);
}


QDiscordRoute QDiscordRoutes::Messages::removeReaction(const QDiscordID& channel, const QDiscordID& message, const QString& reactionCode, const QDiscordID& user)
{
	return QDiscordRoute(QDiscordRoute::Method::DELETE, QDiscordUtilities::endPoints.channels + "/{channel}/messages/{message}/reactions/{reaction}/{user}", channel.toString(), message.toString(), reactionCode, user.toString());
}


QDiscordRoute QDiscordRoutes::Messages::removeAllReactions(const QDiscordID& channel, const QDiscordID& message)
{
	return QDiscordRoute(QDiscordRoute::Method::DELETE, QDiscordUtilities::endPoints.channels + "/{channel}/messages/{message}/reactions", channel.toString(), message.toString());
}


QDiscordRoute QDiscordRoutes::Messages::getReactionUsers(const QDiscordID& channel, const QDiscordID& message, const QString& reactionCode, int limit)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.channels + "/{channel}/messages/{message}" "/reactions/{reaction}?limit={limit}",
		channel.toString(), message.toString(), reactionCode, QString::number(limit));
}


QDiscordRoute QDiscordRoutes::Messages::getMessageHistory(const QDiscordID& channel, int limit)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.channels + "/{channel}/messages?limit={limit}", channel.toString(), QString::number(limit));
}


QDiscordRoute QDiscordRoutes::Messages::getMessageHistoryBefore(const QDiscordID& channel, int limit, const QDiscordID& before)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.channels  + "/{channel}/messages?limit={limit}&before={before}", channel.toString(), QString::number(limit), before.toString());
}


QDiscordRoute QDiscordRoutes::Messages::getMessageHistoryAfter(const QDiscordID& channel, int limit, const QDiscordID& after)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.channels + "/{channel}/messages?limit={limit}&after={after}", channel.toString(), QString::number(limit), after.toString());
}


QDiscordRoute QDiscordRoutes::Messages::getMessageHistoryAround(const QDiscordID& channel, int limit, const QDiscordID& around)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.channels + "/{channel}/messages?limit={limit}&around={around}", channel.toString(), QString::number(limit), around.toString());
}


QDiscordRoute QDiscordRoutes::Messages::getMessage(const QDiscordID& channel, const QDiscordID& message)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.channels + "/{channel}/messages/{message}", channel.toString(), message.toString());
}


QDiscordRoute QDiscordRoutes::Messages::deleteMessages(const QDiscordID& channel)
{
	return QDiscordRoute(QDiscordRoute::Method::POST, QDiscordUtilities::endPoints.channels + "/{channel}/messages/bulk-delete", channel.toString());
}


// Invites
QDiscordRoute QDiscordRoutes::Invites::getInvite(const QString& code)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.invites + "/{code}", code);
}


QDiscordRoute QDiscordRoutes::Invites::deleteInvite(const QString& code)
{
	return QDiscordRoute(QDiscordRoute::Method::DELETE, QDiscordUtilities::endPoints.invites + "/{code}", code);
}


QDiscordRoute QDiscordRoutes::Invites::getGuildInvites(const QDiscordID& guild)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.guilds + "/{guild}/invites", guild.toString());
}


QDiscordRoute QDiscordRoutes::Invites::getChannelInvites(const QDiscordID& channel)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.channels + "/{channel}/invites", channel.toString());
}


QDiscordRoute QDiscordRoutes::Invites::createInvite(const QDiscordID& channel)
{
	return QDiscordRoute(QDiscordRoute::Method::POST, QDiscordUtilities::endPoints.channels + "/{channel}/invites", channel.toString());
}


QDiscordRoute QDiscordRoutes::Invites::acceptInvite(const QString& code)
{
	return QDiscordRoute(QDiscordRoute::Method::POST, QDiscordUtilities::endPoints.invites + "/{code}", code);
}


QDiscordRoute QDiscordRoutes::Messages::ackMessage(const QDiscordID& channel, const QDiscordID& message)
{
	return QDiscordRoute(QDiscordRoute::Method::POST, QDiscordUtilities::endPoints.channels + "/{channel}/messages/{message}/ack", channel.toString(), message.toString());
}


QDiscordRoute QDiscordRoutes::Interactions::createInteractionResponse(const QDiscordID& interaction_id, const QString& interaction_token)
{
	return QDiscordRoute(QDiscordRoute::Method::POST, QDiscordUtilities::endPoints.interactions + "/{interaction_id}/{interaction_token}/callback", interaction_id.toString(), interaction_token);
}


QDiscordRoute QDiscordRoutes::Interactions::getOriginalInteractionResponse(const QDiscordID& application_id, const QString& interaction_token)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.webhooks + "/{application_id}/{interaction_token}/messages/@original", application_id.toString(), interaction_token);
}


QDiscordRoute QDiscordRoutes::Interactions::editOriginalInteractionResponse(const QDiscordID& application_id, const QString& interaction_token)
{
	return QDiscordRoute(QDiscordRoute::Method::PATCH, QDiscordUtilities::endPoints.webhooks + "/{application_id}/{interaction_token}/messages/@original", application_id.toString(), interaction_token);
}


QDiscordRoute QDiscordRoutes::Interactions::deleteOriginalInteractionResponse(const QDiscordID& application_id, const QString& interaction_token)
{
	return QDiscordRoute(QDiscordRoute::Method::DELETE, QDiscordUtilities::endPoints.webhooks + "/{application_id}/{interaction_token}/messages/@original", application_id.toString(), interaction_token);
}


QDiscordRoute QDiscordRoutes::Interactions::createFollowupMessage(const QDiscordID& application_id, const QString& interaction_token)
{
	return QDiscordRoute(QDiscordRoute::Method::POST, QDiscordUtilities::endPoints.webhooks + "/{application_id}/{interaction_token}", application_id.toString(), interaction_token);
}


QDiscordRoute QDiscordRoutes::Interactions::getFollowupMessage(const QDiscordID& application_id, const QString& interaction_token, const QDiscordID& message_id)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.webhooks + "/{application_id}/{interaction_token}/messages/{message_id}", application_id.toString(), interaction_token, message_id.toString());
}


QDiscordRoute QDiscordRoutes::Interactions::editFollowupMessage(const QDiscordID& application_id, const QString& interaction_token, const QDiscordID& message_id)
{
	return QDiscordRoute(QDiscordRoute::Method::PATCH, QDiscordUtilities::endPoints.webhooks + "/{application_id}/{interaction_token}/messages/{message_id}", application_id.toString(), interaction_token, message_id.toString());
}


QDiscordRoute QDiscordRoutes::Interactions::deleteFollowupMessage(const QDiscordID& application_id, const QString& interaction_token, const QDiscordID& message_id)
{
	return QDiscordRoute(QDiscordRoute::Method::DELETE, QDiscordUtilities::endPoints.webhooks + "/{application_id}/{interaction_token}/messages/{message_id}", application_id.toString(), interaction_token, message_id.toString());
}


QDiscordRoute QDiscordRoutes::ApplicationCommands::getGlobalCommands(const QDiscordID& application_id)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.applications + "/{application_id}/commands", application_id.toString());
}


QDiscordRoute QDiscordRoutes::ApplicationCommands::overwriteGlobalCommands(const QDiscordID& application_id)
{
	return QDiscordRoute(QDiscordRoute::Method::PUT, QDiscordUtilities::endPoints.applications + "/{application_id}/commands", application_id.toString());
}


QDiscordRoute QDiscordRoutes::ApplicationCommands::getGlobalCommand(const QDiscordID& application_id, const QDiscordID& command_id)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.applications + "/{application_id}/commands/{command_id}", application_id.toString(), command_id.toString());
}


QDiscordRoute QDiscordRoutes::ApplicationCommands::createGlobalCommand(const QDiscordID& application_id)
{
	return QDiscordRoute(QDiscordRoute::Method::POST, QDiscordUtilities::endPoints.applications + "/{application_id}/commands", application_id.toString());
}


QDiscordRoute QDiscordRoutes::ApplicationCommands::editGlobalCommand(const QDiscordID& application_id, const QDiscordID& command_id)
{
	return QDiscordRoute(QDiscordRoute::Method::PATCH, QDiscordUtilities::endPoints.applications + "/{application_id}/commands/{command_id}", application_id.toString(), command_id.toString());
}


QDiscordRoute QDiscordRoutes::ApplicationCommands::deleteGlobalCommand(const QDiscordID& application_id, const QDiscordID& command_id)
{
	return QDiscordRoute(QDiscordRoute::Method::DELETE, QDiscordUtilities::endPoints.applications + "/{application_id}/commands/{command_id}", application_id.toString(), command_id.toString());
}


QDiscordRoute QDiscordRoutes::ApplicationCommands::getGuildCommands(const QDiscordID& application_id, const QDiscordID& guild_id)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.applications + "/{application_id}/guilds/{guild_id}/commands", application_id.toString(), guild_id.toString());
}


QDiscordRoute QDiscordRoutes::ApplicationCommands::overwriteGuildCommands(const QDiscordID& application_id, const QDiscordID& guild_id)
{
	return QDiscordRoute(QDiscordRoute::Method::PUT, QDiscordUtilities::endPoints.applications + "/{application_id}/guilds/{guild_id}/commands", application_id.toString(), guild_id.toString());
}


QDiscordRoute QDiscordRoutes::ApplicationCommands::getGuildCommand(const QDiscordID& application_id, const QDiscordID& guild_id, const QDiscordID& command_id)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.applications + "/{application_id}/guilds/{guild_id}/commands/{command_id}", application_id.toString(), guild_id.toString(), command_id.toString());
}


QDiscordRoute QDiscordRoutes::ApplicationCommands::createGuildCommand(const QDiscordID& application_id, const QDiscordID& guild_id)
{
	return QDiscordRoute(QDiscordRoute::Method::POST, QDiscordUtilities::endPoints.applications + "/{application_id}/guilds/{guild_id}/commands", application_id.toString(), guild_id.toString());
}


QDiscordRoute QDiscordRoutes::ApplicationCommands::editGuildCommand(const QDiscordID& application_id, const QDiscordID& guild_id, const QDiscordID& command_id)
{
	return QDiscordRoute(QDiscordRoute::Method::PATCH, QDiscordUtilities::endPoints.applications + "/{application_id}/guilds/{guild_id}/commands/{command_id}", application_id.toString(), guild_id.toString(), command_id.toString());
}


QDiscordRoute QDiscordRoutes::ApplicationCommands::deleteGuildCommand(const QDiscordID& application_id, const QDiscordID& guild_id, const QDiscordID& command_id)
{
	return QDiscordRoute(QDiscordRoute::Method::DELETE, QDiscordUtilities::endPoints.applications + "/{application_id}/guilds/{guild_id}/commands/{command_id}", application_id.toString(), guild_id.toString(), command_id.toString());
}


QDiscordRoute QDiscordRoutes::ApplicationCommands::getGuildCommandsPermissions(const QDiscordID& application_id, const QDiscordID& guild_id)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.applications + "/{application_id}/guilds/{guild_id}/commands/permissions", application_id.toString(), guild_id.toString());
}


QDiscordRoute QDiscordRoutes::ApplicationCommands::putGuildCommandsPermissions(const QDiscordID& application_id, const QDiscordID& guild_id)
{
	return QDiscordRoute(QDiscordRoute::Method::PUT, QDiscordUtilities::endPoints.applications + "/{application_id}/guilds/{guild_id}/commands/permissions", application_id.toString(), guild_id.toString());
}


QDiscordRoute QDiscordRoutes::ApplicationCommands::getGuildCommandPermissions(const QDiscordID& application_id, const QDiscordID& guild_id, const QDiscordID& command_id)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.applications + "/{application_id}/guilds/{guild_id}/commands/{command_id}/permissions", application_id.toString(), guild_id.toString(), command_id.toString());
}


QDiscordRoute QDiscordRoutes::ApplicationCommands::editGuildCommandPermissions(const QDiscordID& application_id, const QDiscordID& guild_id, const QDiscordID& command_id)
{
	return QDiscordRoute(QDiscordRoute::Method::PUT, QDiscordUtilities::endPoints.applications + "/{application_id}/guilds/{guild_id}/commands/{command_id}/permissions", application_id.toString(), guild_id.toString(), command_id.toString());
}


QDiscordRoute QDiscordRoutes::Avatars::getAvatarPng(const QDiscordID& user_id, const QString& avatar_hash)
{
	return QDiscordRoute(QDiscordRoute::Method::GET, QDiscordUtilities::endPoints.discordFilesBase + "/avatars/{user_id}/{avatar_hash}.png", user_id.toString(), avatar_hash);
}


QDebug& operator<<(QDebug& d, const QDiscordRoute& route)
{
	d.nospace() << "QDiscordRoute(Method: ";
	switch (route.method())
	{
	case QDiscordRoute::Method::DELETE:
		d << "DELETE";
		break;
	case QDiscordRoute::Method::GET:
		d << "GET";
		break;
	case QDiscordRoute::Method::PATCH:
		d << "PATCH";
		break;
	case QDiscordRoute::Method::POST:
		d << "POST";
		break;
	case QDiscordRoute::Method::PUT:
		d << "PUT";
		break;
	default:
		d << "?";
	}
	d << " Full URL: " << route.fullUrl();
	d << " Bucket URL: " << route.bucketUrl();
	d << ")";
	return d.maybeSpace();
}


