
// Copyright(c) 2022 by wad(wad@inbox.lv)

#pragma once

#include "QDiscordModel.h"
#include "QDiscordEmoji.h"


enum class MessageComponentType : qint8
{
	ActionRow  = 1, // A container for other components
	Button     = 2, // A button object
	SelectMenu = 3, // A select menu for picking from choices
	TextInput  = 4, // A text input object
	Unknown    = -1
};


class QDiscordMessageComponent
	: public SerializableJson
{
	Q_GADGET
	Q_ENUM(MessageComponentType)
public:
	QDiscordMessageComponent() = delete;
	QDiscordMessageComponent(MessageComponentType type) : _type(type) {}
	static QSharedPointer<QDiscordMessageComponent> fromJson(const QJsonObject& object);
	virtual void deserialize(const QJsonObject& object) = 0;
	virtual QJsonObject serialize() const = 0;

	const MessageComponentType type() const { return _type; }

protected:
	MessageComponentType _type = MessageComponentType::Unknown;
};
Q_DECLARE_METATYPE(QDiscordMessageComponent)


class QDiscordMessageComponent_ActionRow
	: public QDiscordMessageComponent
	, public QDiscordModelBase<QDiscordMessageComponent_ActionRow>
{
	Q_GADGET
public:
	QDiscordMessageComponent_ActionRow() : QDiscordMessageComponent(MessageComponentType::ActionRow) {}
	void deserialize(const QJsonObject& object) override;
	QJsonObject serialize() const override;

	const QList<QSharedPointer<QDiscordMessageComponent>>& components() const { return _components; }
	void clearComponents() { _components.clear(); }
	void addComponent(QSharedPointer<QDiscordMessageComponent> component) { _components.append(component); }
	void setComponents(const QList<QSharedPointer<QDiscordMessageComponent>>& components) { _components = components; }

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._type, "type");
		field(a, self._components, "components");
	}

private:
	QList<QSharedPointer<QDiscordMessageComponent>> _components;
};
Q_DECLARE_METATYPE(QDiscordMessageComponent_ActionRow)


class QDiscordMessageComponent_Button
	: public QDiscordMessageComponent
	, public QDiscordModelBase<QDiscordMessageComponent_Button>
{
	Q_GADGET
public:
	enum class ButtonStyle : qint8
	{
		Primary   = 1, // blurple custom_id
		Secondary = 2, // grey    custom_id
		Success   = 3, // green   custom_id
		Danger    = 4, // red     custom_id
		Link      = 5, // grey,   navigates to a URL url
		Unknown   = -1
	};
	Q_ENUM(ButtonStyle)

	QDiscordMessageComponent_Button() : QDiscordMessageComponent(MessageComponentType::Button) {}
	void deserialize(const QJsonObject& object) override;
	QJsonObject serialize() const override;

	const ButtonStyle& style() const { return _style; }
	void setStyle(ButtonStyle style) { _style = style; }
	const std::optional<QString>& label() const { return _label; }
	void setLabel(const QString& label) { _label = label; }
	const std::optional<QDiscordEmoji>& emoji() const { return _emoji; }
	void setEmoji(const QDiscordEmoji& emoji) { _emoji = emoji; }
	const std::optional<QString>& custom_id() const { return _custom_id; }
	void setCustom_id(const QString& custom_id) { _custom_id = custom_id; }
	const std::optional<QString>& url() const { return _url; }
	void setUrl(const QString& url) { _url = url; }
	const std::optional<bool>& disabled() const { return _disabled; }
	void setDisabled(const bool disabled) { _disabled = disabled; }

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._type, "type");
		field(a, self._style, "style");
		field(a, self._label, "label");
		field(a, self._emoji, "emoji");
		field(a, self._custom_id, "custom_id");
		field(a, self._url, "url");
		field(a, self._disabled, "disabled");
	}

private:
	ButtonStyle                  _style = ButtonStyle::Unknown;
	std::optional<QString>       _label;     // text that appears on the button, max 80 characters
	std::optional<QDiscordEmoji> _emoji;     // partial emoji - name, id, and animated
	std::optional<QString>       _custom_id; // a developer-defined identifier for the button, max 100 characters
	std::optional<QString>       _url;       // a url for link-style buttons
	std::optional<bool>          _disabled;  // whether the button is disabled (default false)
};
Q_DECLARE_METATYPE(QDiscordMessageComponent_Button)


class QDiscordSelectMenuOption
	: public QDiscordModelBase<QDiscordSelectMenuOption>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordSelectMenuOption> fromJson(const QJsonObject& object);
	QDiscordSelectMenuOption(const QJsonObject& object);
	QDiscordSelectMenuOption() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	const QString& label() const { return _label; }
	void setLabel(const QString& label) { _label = label; }
	const QString& value() const { return _value; }
	void setValue(const QString& value) { _value = value; }
	const std::optional<QString>& description() const { return _description; }
	void setDescription(const QString& description) { _description = description; }
	const std::optional<QDiscordEmoji>& emoji() const { return _emoji; }
	void setDescription(const QDiscordEmoji& emoji) { _emoji = emoji; }
	const std::optional<bool>& default_() const { return _default; }
	void setDefault(const bool default_) { _default = default_; }

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._label, "label");
		field(a, self._value, "value");
		field(a, self._description, "description");
		field(a, self._emoji, "emoji");
		field(a, self._default, "default");
	}

private:
	QString                      _label;       // the user-facing name of the option, max 100 characters
	QString                      _value;       // the dev-defined value of the option, max 100 characters
	std::optional<QString>       _description; // an additional description of the option, max 100 characters
	std::optional<QDiscordEmoji> _emoji;       // partial emoji - id, name, and animated
	std::optional<bool>          _default;     // will render this option as selected by default
};
Q_DECLARE_METATYPE(QDiscordSelectMenuOption)


class QDiscordMessageComponent_SelectMenu
	: public QDiscordMessageComponent
	, public QDiscordModelBase<QDiscordMessageComponent_SelectMenu>
{
	Q_GADGET
public:
	QDiscordMessageComponent_SelectMenu() : QDiscordMessageComponent(MessageComponentType::SelectMenu) {}
	void deserialize(const QJsonObject& object) override;
	QJsonObject serialize() const override;

	const QString& custom_id() const { return _custom_id; }
	void setCustom_id(const QString& custom_id) { _custom_id = custom_id; }
	const QList<QDiscordSelectMenuOption>& options() const { return _options; }
	void setOptions(const QList<QDiscordSelectMenuOption>& options) { _options = options; }
	void addOption(const QDiscordSelectMenuOption& option) { _options.append(option); }

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._type, "type");
		field(a, self._custom_id, "custom_id");
		field(a, self._options, "options");
		field(a, self._placeholder, "placeholder");
		field(a, self._min_values, "min_values");
		field(a, self._max_values, "max_values");
		field(a, self._disabled, "disabled");
	}

private:
	QString                         _custom_id;   // a developer-defined identifier for the button, max 100 characters
	QList<QDiscordSelectMenuOption> _options;     // array of select options	the choices in the select, max 25
	std::optional<QString>          _placeholder; // custom placeholder text if nothing is selected, max 150 characters
	std::optional<int>              _min_values;  // the minimum number of items that must be chosen; default 1, min 0, max 25
	std::optional<int>              _max_values;  // the maximum number of items that can be chosen; default 1, max 25
	std::optional<bool>             _disabled;    // disable the select, default false
};
Q_DECLARE_METATYPE(QDiscordMessageComponent_SelectMenu)


class QDiscordMessageComponent_TextInput
	: public QDiscordMessageComponent
	, public QDiscordModelBase<QDiscordMessageComponent_TextInput>
{
	Q_GADGET
public:
	enum class TextInputStyle : qint8
	{
		Short     = 1, // A single-line input
		Paragraph = 2, // A multi-line input
		Unknown   = -1
	};
	Q_ENUM(TextInputStyle)

	QDiscordMessageComponent_TextInput() : QDiscordMessageComponent(MessageComponentType::TextInput) {}
	void deserialize(const QJsonObject& object) override;
	QJsonObject serialize() const override;

	const QString& custom_id() const { return _custom_id; }
	void setCustom_id(const QString& custom_id) { _custom_id = custom_id; }
	const TextInputStyle style() const { return _style; }
	void setStyle(const TextInputStyle style) { _style = style; }
	const QString& label() const { return _label; }
	void setLabel(const QString& label) { _label = label; }
	const std::optional<int>& min_length() const { return _min_length; }
	void setMin_length(const int min_length) { _min_length = min_length; }
	const std::optional<int>& max_length() const { return _max_length; }
	void setMax_length(const int max_length) { _max_length = max_length; }
	const std::optional<bool>& required() const { return _required; }
	void setRequired(const bool required) { _required = required; }
	const std::optional<QString>& value() const { return _value; }
	void setValue(const QString& value) { _value = value; }
	const std::optional<QString>& placeholder() const { return _placeholder; }
	void setPlaceholder(const QString& placeholder) { _placeholder = placeholder; }

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._type, "type");
		field(a, self._custom_id, "custom_id");
		field(a, self._style, "style");
		field(a, self._label, "label");
		field(a, self._min_length, "min_length");
		field(a, self._max_length, "max_length");
		field(a, self._required, "required");
		field(a, self._value, "value");
		field(a, self._placeholder, "placeholder");
	}

private:
	QString                 _custom_id;  // a developer-defined identifier for the button, max 100 characters
	TextInputStyle          _style = TextInputStyle::Unknown;
	QString                 _label;      // the label for this component, max 45 characters
	std::optional<int>      _min_length; // the minimum input length for a text input, min 0, max 4000
	std::optional<int>      _max_length; // the maximum input length for a text input, min 1, max 4000
	std::optional<bool>     _required;   // whether this component is required to be filled, default true
	std::optional<QString>  _value;      // a pre-filled value for this component, max 4000 characters
	std::optional<QString>  _placeholder; // custom placeholder text if the input is empty, max 100 characters
};
Q_DECLARE_METATYPE(QDiscordMessageComponent_TextInput)


namespace QDiscordModel
{
template<>
void field(QDiscordModel::DeserializeJsonAction& action, MessageComponentType& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const MessageComponentType& value, const QString& name);
template<>
void field(QDiscordModel::DeserializeJsonAction& action, QDiscordMessageComponent_Button::ButtonStyle& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QDiscordMessageComponent_Button::ButtonStyle& value, const QString& name);
template<>
void field(QDiscordModel::DeserializeJsonAction& action, QDiscordMessageComponent_TextInput::TextInputStyle& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QDiscordMessageComponent_TextInput::TextInputStyle& value, const QString& name);
} // namespace QDiscordModel


