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

#include "QDiscordLogging.h"


/*!
 * \brief A namespace containing configuration variables and functions used in
 * %QDiscord.
 */
namespace QDiscordUtilities
{
	///\brief A struct used for storing the Discord API endpoints.
	struct EndPoints
	{
		QString discordBase;
		QString discordFilesBase;
		QString apiBase;          ///<\brief The base Discord API endpoint.
		QString gateway;          ///<\brief The gateway endpoint.
		QString users;            ///<\brief The users endpoint.
		QString me;               ///<\brief The users/\@me endpoint.
		QString guilds;           ///<\brief THe guilds endpoint.
		QString auth;             ///<\brief The auth endpoint.
		QString register_;        ///<\brief The registration endpoint.
		QString login;            ///<\brief The auth/login endpoint.
		QString logout;           ///<\brief The auth/logout endpoint.
		QString servers;          ///<\brief The servers endpoint.
		QString channels;         ///<\brief The channels endpoint.
		QString invites;          ///<\brief The invites endpoint.
		QString interactions;     ///<\brief The interactions endpoint.
		QString webhooks;         ///<\brief The interactions endpoint.
		QString applications;     ///<\brief The interactions endpoint.
	};
	extern const EndPoints endPoints;
	/*!
	 * \brief Converts network errors to a human-readable string based on
	 * Discord documentation.
	 *
	 * See https://discordapp.com/developers/docs/topics/response-codes
	 * \param error The network error returned by a failed method.
	 */
	QString networkErrorToString(QNetworkReply::NetworkError error);
	///\brief Discord's epoch value for snowflake generation.
	extern const qlonglong discordEpoch;
	/*!
	 * \brief The library name.
	 *
	 * This should always be QDiscord, unless you fork the project and change
	 * the name.\n
	 * Change it in `src/config`.
	 */
	extern const QString libName;
	/*!
	 * \brief The name of the bot this library will be used for.
	 *
	 * This should always be changed to your bot's name before QDiscord starts.
	 */
	extern QString botName;
	///\brief The major version of the library.
	extern const QString libMajor;
	/*!
	 * \brief The minor version of the library.
	 *
	 * This should be incremented with each update of the library.
	 */
	extern const QString libMinor;
	///\brief The patch version of the library.
	extern const QString libPatch;
	///\brief A link to where the library repository is located.
	extern const QString libLink;
	///\brief The full library version.
	extern const QString libVersion;
	///\brief The Discord API version in use.
	extern const QString apiVersion;
} // namespace QDiscordUtilities

