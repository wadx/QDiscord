
// Copyright(c) 2022 by wad(wad@inbox.lv)

#pragma once

#include "QDiscordModel.h"
#include "QDiscordId.h"
#include "QDiscordUser.h"
#include "QDiscordTeam.h"
#include "QDiscordPermissions.h"


class QDiscordInstallParams
	: public QDiscordModelBase<QDiscordInstallParams>
{
	Q_GADGET

public:
	static QSharedPointer<QDiscordInstallParams> fromJson(const QJsonObject& object);
	QDiscordInstallParams(const QJsonObject& object);
	QDiscordInstallParams() = default;
	void deserialize(const QJsonObject & object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._scopes, "scopes");
		field(a, self._permissions, "permissions");
	}

private:
	QList<QString>      _scopes;      // the scopes to add the application to the server with
	QDiscordPermissions _permissions; // the permissions to request for the bot role
};
Q_DECLARE_METATYPE(QDiscordInstallParams)


class QDiscordApplication
	: public QDiscordModelBase<QDiscordApplication>
{
	Q_GADGET
public:
	enum class ApplicationFlags : qint32
	{
		GATEWAY_PRESENCE                 = 1 << 12, // Intent required for bots in 100 or more servers to receive presence_update events
		GATEWAY_PRESENCE_LIMITED         = 1 << 13, // Intent required for bots in under 100 servers to receive presence_update events, found in Bot Settings
		GATEWAY_GUILD_MEMBERS            = 1 << 14, // Intent required for bots in 100 or more servers to receive member-related events like guild_member_add. See list of member-related events under GUILD_MEMBERS
		GATEWAY_GUILD_MEMBERS_LIMITED    = 1 << 15, // Intent required for bots in under 100 servers to receive member-related events like guild_member_add, found in Bot Settings. See list of member-related events under GUILD_MEMBERS
		VERIFICATION_PENDING_GUILD_LIMIT = 1 << 16, // Indicates unusual growth of an app that prevents verification
		EMBEDDED                         = 1 << 17, // Indicates if an app is embedded within the Discord client (currently unavailable publicly)
		GATEWAY_MESSAGE_CONTENT          = 1 << 18, // Intent required for bots in 100 or more servers to receive message content
		GATEWAY_MESSAGE_CONTENT_LIMITED  = 1 << 19  // Intent required for bots in under 100 servers to receive message content, found in Bot Settings
	};

	static QSharedPointer<QDiscordApplication> fromJson(const QJsonObject& object);
	QDiscordApplication(const QJsonObject& object);
	QDiscordApplication() = default;
	void deserialize(const QJsonObject & object);
	QJsonObject serialize() const;

	const QDiscordID& id() const { return _id; }
	void setId(const QDiscordID& id) { _id = id; }

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._id, "id");
		field(a, self._name, "name");
		field(a, self._icon, "icon");
		field(a, self._description, "description");
		field(a, self._rpc_origins, "rpc_origins");
		field(a, self._bot_public, "bot_public");
		field(a, self._bot_require_code_grant, "bot_require_code_grant");
		field(a, self._terms_of_service_url, "terms_of_service_url");
		field(a, self._privacy_policy_url, "privacy_policy_url");
		field(a, self._owner, "owner");
		field(a, self._verify_key, "verify_key");
		field(a, self._team, "team");
		field(a, self._guild_id, "guild_id");
		field(a, self._primary_sku_id, "primary_sku_id");
		field(a, self._slug, "slug");
		field(a, self._cover_image, "cover_image");
		field(a, self._flags, "flags");
		field(a, self._tags, "tags");
		field(a, self._install_params, "install_params");
		field(a, self._custom_install_url, "custom_install_url");
	}

private:
	QDiscordID                           _id; // the id of the app
	QString                              _name; // the name of the app
	std::optional<QString>               _icon; // the icon hash of the app
	QString                              _description; // the description of the app
	QList<QString>                       _rpc_origins; // an array of rpc origin urls, if rpc is enabled
	bool                                 _bot_public; // when false only app owner can join the app's bot to guilds
	bool                                 _bot_require_code_grant; // when true the app's bot will only join upon completion of the full oauth2 code grant flow
	std::optional<QString>               _terms_of_service_url; // the url of the app's terms of service
	std::optional<QString>               _privacy_policy_url; // the url of the app's privacy policy
	std::optional<QDiscordUser>          _owner; // partial user object containing info on the owner of the application
	QString                              _verify_key; // the hex encoded key for verification in interactions and the GameSDK's GetTicket
	std::optional<QDiscordTeam>          _team; // if the application belongs to a team, this will be a list of the members of that team
	std::optional<QDiscordID>            _guild_id; // if this application is a game sold on Discord, this field will be the guild to which it has been linked
	std::optional<QDiscordID>            _primary_sku_id; // if this application is a game sold on Discord, this field will be the id of the "Game SKU" that is created, if exists
	std::optional<QString>               _slug; // if this application is a game sold on Discord, this field will be the URL slug that links to the store page
	std::optional<QString>               _cover_image; // the application's default rich presence invite cover image hash
	std::optional<int>                   _flags; // the application's public flags (ApplicationFlags)
	QList<QString>                       _tags; // up to 5 tags describing the content and functionality of the application
	std::optional<QDiscordInstallParams> _install_params; // settings for the application's default in-app authorization link, if enabled
	std::optional<QString>               _custom_install_url; // the application's default custom authorization link, if enabled
};
Q_DECLARE_METATYPE(QDiscordApplication)

