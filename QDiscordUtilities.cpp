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
#include "QDiscordUtilities.h"

#ifdef QDISCORD_NAME
const QString QDiscordUtilities::libName = QDISCORD_NAME;
#else
const QString QDiscordUtilities::libName = "QDiscord";
#endif
#ifdef QDISCORD_LINK
const QString QDiscordUtilities::libLink = QDISCORD_LINK;
#else
const QString QDiscordUtilities::libLink = "https://gitlab.com/george99g/QDiscord";
#endif
#ifdef QDISCORD_VERSION_MAJOR
const QString QDiscordUtilities::libMajor = QDISCORD_VERSION_MAJOR;
#else
const QString QDiscordUtilities::libMajor = "?";
#endif
#ifdef QDISCORD_VERSION_MINOR
const QString QDiscordUtilities::libMinor = QDISCORD_VERSION_MINOR;
#else
const QString QDiscordUtilities::libMinor = "?";
#endif
#ifdef QDISCORD_VERSION_PATCH
const QString QDiscordUtilities::libPatch = QDISCORD_VERSION_PATCH;
#else
const QString QDiscordUtilities::libPatch = "?";
#endif

#ifdef QDISCORD_VERSION
const QString QDiscordUtilities::libVersion = QDISCORD_VERSION;
#else
const QString QDiscordUtilities::libVersion = "?.?.?";
#endif

QString QDiscordUtilities::botName = "Unnamed QDiscord-based bot";

const QString QDiscordUtilities::apiVersion = "9";

const qlonglong QDiscordUtilities::discordEpoch = 1420070400000;


const QDiscordUtilities::EndPoints QDiscordUtilities::endPoints = []() -> QDiscordUtilities::EndPoints
{
	QDiscordUtilities::EndPoints init;
	init.discordBase = "https://discord.com";
	init.discordFilesBase = "https://cdn.discordapp.com";
	init.apiBase = init.discordBase + "/api/v" + apiVersion;
	init.gateway = init.apiBase + "/gateway?encoding=json&v=" + apiVersion;
	init.users = init.apiBase + "/users";
	init.me = init.users + "/@me";
	init.guilds = init.apiBase + "/guilds";
	init.auth = init.apiBase + "/auth";
	init.register_ = init.auth + "/register";
	init.login = init.auth + "/login";
	init.logout = init.auth + "/logout";
	init.servers = init.apiBase + "/guilds";
	init.channels = init.apiBase + "/channels";
	init.invites = init.apiBase + "/invites";
	init.interactions = init.apiBase + "/interactions";
	init.webhooks = init.apiBase + "/webhooks";
	init.applications = init.apiBase + "/applications";
	return init;
}();


QString QDiscordUtilities::networkErrorToString(QNetworkReply::NetworkError error)
{
	switch ((int)error)
	{
	case 200:
		return "200 (OK): The response completed sucessfully.";
	case 201:
		return "200 (CREATED): The entity was created successfully.";
	case 304:
		return "304 (NOT MODIFIED): The entity was not modified (no action was "
			"taken).";
	case 400:
		return "400 (BAD REQUEST): The request was improperly formatted, or "
			"the "
			"server couldn't understand it.";
	case 401:
		return "401 (UNAUTHORIZED): The Authorization header was missing or "
			"invalid.";
	case 403:
		return "403 (FORBIDDEN): The Authorization token you passed did not "
			"have "
			"permission to the resource";
	case 404:
		return "404 (NOT FOUND): The resource at the location specified "
			"doesn't "
			"exist.";
	case 405:
		return "405 (METHOD NOT ALLOWED): The HTTP method used is not valid "
			"for "
			"the location specified.";
	case 429:
		return "429 (TOO MANY REQUESTS): You've made too many requests.";
	case 502:
		return "502 (GATEWAY UNAVAILABLE): There was not a gateway available "
			"to "
			"process your request. Wait a bit and retry.";
	default:
		if ((int)error > 499 && (int)error < 600)
			return "5xx (SERVER ERROR): The server had an error processing "
			"your "
			"request.";
		else
			return "xxx (UNKNOWN): Unknown error.";
	}
}


