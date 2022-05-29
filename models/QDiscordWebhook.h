
// Copyright(c) 2022 by wad(wad@inbox.lv)

#pragma once

#include "QDiscordModel.h"
#include "QDiscordId.h"
#include "QDiscordEmbed.h"
#include "QDiscordChannelMention.h"
#include "QDiscordAttachment.h"


class QDiscordWebhook
	: public QDiscordModelBase<QDiscordWebhook>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordWebhook> fromJson(const QJsonObject& object);
	QDiscordWebhook(const QJsonObject& object);
	QDiscordWebhook() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	void sendCreate(QDiscordRest& rest, const QDiscordID& applicationId, const QString& interactionToken, const std::optional<bool>& wait, std::optional<QDiscordID>& threadId, const std::function<void(QSharedPointer<QDiscordMessage>)>& callback = nullptr);

	const std::optional<QString>& content() const { return _content; }
	void setContent(const QString& content) { _content = content; }
	const std::optional<QString>& username() const { return _username; }
	void setUsername(const QString& username) { _username = username; }
	const std::optional<QString>& avatar_url() const { return _avatar_url; }
	void setAvatar_url(const QString& avatar_url) { _avatar_url = avatar_url; }
	const std::optional<bool>& tts() const { return _tts; }
	void setTts(bool tts) { _tts = tts; }
	const QList<QSharedPointer<QDiscordEmbed>>& embeds() const { return _embeds; }
	void addEmbed(QSharedPointer<QDiscordEmbed> embed) { _embeds.append(embed); }
	const QSharedPointer<QDiscordAllowedMentions>& allowed_mentions() const { return _allowed_mentions; }
	void setAllowed_mentions(QSharedPointer<QDiscordAllowedMentions> allowed_mentions) { _allowed_mentions = allowed_mentions; }
	const QList<QSharedPointer<QDiscordMessageComponent>>& components() const { return _components; }
	void addComponent(QSharedPointer<QDiscordMessageComponent> component) { _components.append(component); }
	const QList<QSharedPointer<QDiscordAttachment>>& attachments() const { return _attachments; }
	const QList<QByteArray>& attachmentsFiles() const { return _files; }
	void addAttachment(const QSharedPointer<QDiscordAttachment>& attachment, const QByteArray& data) { _attachments.append(attachment); _files.append(data); }
	const std::optional<int>& flags() const { return _flags; }
	void setFlags(int flags) { _flags = flags; }

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._content, "content");
		field(a, self._username, "username");
		field(a, self._avatar_url, "avatar_url");
		field(a, self._tts, "tts");
		field(a, self._embeds, "embeds");
		field(a, self._allowed_mentions, "allowed_mentions");
		field(a, self._components, "components");
		field(a, self._payload_json, "payload_json");
		field(a, self._attachments, "attachments");
		field(a, self._flags, "flags");
	}

private:
	// required one of: content, file, embeds
	std::optional<QString>                          _content;          // the message contents (up to 2000 characters)
	std::optional<QString>                          _username;         // override the default username of the webhook (not supported in fullow up messages)
	std::optional<QString>                          _avatar_url;       // override the default avatar of the webhook (not supported in fullow up messages)
	std::optional<bool>                             _tts;              // true if this is a TTS message
	QList<QSharedPointer<QDiscordEmbed>>            _embeds;           // embedded rich content
	QSharedPointer<QDiscordAllowedMentions>         _allowed_mentions; // allowed mentions for the message
	QList<QSharedPointer<QDiscordMessageComponent>> _components;       // the components to include with the message
	std::optional<QString>                          _payload_json;     // JSON encoded body of non-file params. multipart/form-data only
	QList<QSharedPointer<QDiscordAttachment>>       _attachments;      // array of partial attachment objects	attachment objects with filename and description
	std::optional<int>                              _flags;            // message flags combined as a bitfield (only SUPPRESS_EMBEDS can be set)

	QList<QByteArray>                               _files;
};
Q_DECLARE_METATYPE(QDiscordWebhook)


