#include <string>
#include "messages.h"

using std::string;

bool VK::DialogInfo::parse(const json &data) {
    if(data == nullptr) {
        return false;
    }

    try {

        this->title = data.at("title").get<string>();
        if(this->title == " ... " || this->title.empty()) {
            this->title = "";
        }
        this->body = data.at("body").get<string>();
        if(data.find("chat_id") != data.end()) {
            this->chat_id = data.at("chat_id").get<int>() + chat_offset;
            this->is_chat = true;
        } else {
            this->chat_id = data.at("user_id").get<int>();
            this->is_chat = false;
        }
        if(body.empty()) {
            body = "...";
        }
        return true;
    }
    catch(...) {

    }

    return false;
}

bool VK::DialogInfo::parse(const json& data1, const json& data2)
{
	if(data1 == nullptr || data2 == nullptr) {
        return false;
    }

	json item_last_msg = data1.at("last_message").get<json>();
	json item_conversation = data1.at("conversation").get<json>();

    try {
        if (item_conversation.at("peer").get<json>().at("type").get<string>() == "user")
    	{
    		this->chat_id = item_conversation.at("peer").get<json>().at("id").get<int>();
    		this->is_chat = false;
    	}
        else
        {
	        this->chat_id = item_conversation.at("peer").get<json>().at("id").get<int>() + chat_offset;
        	this->is_chat = true;
        }
        if(is_chat) {
            this->title = item_conversation.at("chat_settings").get<json>().at("title").get<string>();
        	this->from_id = item_last_msg.at("from_id").get<int>();
        	photo_url = item_conversation.at("photo").get<json>().at("photo_50").get<string>();
        }
        else
        {
	        photo_url = data2.at("photo_50").get<string>();
        }
        this->body = item_last_msg.at("text").get<string>();
        if(body.empty()) {
            body = "...";
        }
        return true;
    }
    catch(...) {

    }

    return false;
}

bool VK::DialogInfo::parse_last_message(const json& data)
{
	if (data == nullptr)
	{
		return false;
	}

	try
	{
        this->body = data.at("text").get<string>();
        this->chat_id = data.at("from_id").get<int>();

		return true;
	}
	catch (...)
	{
		
	}

	return false;
}

bool VK::DialogInfo::parse_conversation(const json& data)
{
	if (data == nullptr)
	{
		return false;
	}

	auto type = data.at("peer").get<json>().at("type").get<string>();

	try
	{
		if (type == "user")
		{
			this->is_chat = false;
		}
        else
        {
	        this->is_chat = true;
        }
	}
	catch (...)
	{
		
	}

	return false;
}

bool VK::DialogInfo::operator==(const DialogInfo& dialog_info)
{
	if (this->body == dialog_info.body && this->chat_id == dialog_info.chat_id && this->photo_url == dialog_info.photo_url)
        return true;
	return false;
}

VK::vector_dialogs VK::Messages::get_dialogs(const size_t count, const size_t offset) {
    VK::vector_dialogs res;

    if(count == 0 || count > 200) {
        return std::move(res);
    }

    VK::params_map params = {
        {"count", std::to_string(count)},
        {"offset", std::to_string(offset)},
        {"preview_length", "20"},
        {"unread", "1"},
    };

    json jres = call("messages.getDialogs", params);
    if(jres == nullptr) {
        return std::move(res);
    }

    if(jres.find("error") == jres.end()) {

        json items = jres.at("response").get<json>().at("items").get<json>();

        for (json::iterator it = items.begin(); it != items.end(); ++it) {
            json item = it.value();
            if(item.find("message") == item.end())
                continue;
            item = item.at("message").get<json>();
            VK::DialogInfo dialog;
            if(dialog.parse(item)) {

                if(dialog.title.empty()) {
                    dialog.title = (dialog.is_chat) ?
                                get_chat_title(dialog.chat_id) : get_username(dialog.chat_id);
                }

                res.push_back(std::move(dialog));
            }
        }
    }

    return std::move(res);
}

VK::vector_dialogs VK::Messages::get_conversations()
{
    VK::vector_dialogs result;
	
	VK::params_map params =
        {
        	{"count", "30"},
        	{"filter", "unread"},
        	{"extended", "1"}
        };

	json jres = call("messages.getConversations", params);

    if (jres == nullptr)
    {
	    return std::move(result);
    }

	if (jres.find("error") == jres.end())
	{
		json items = jres.at("response").get<json>().at("items").get<json>();
    	json profiles = jres.at("response").get<json>().at("profiles").get<json>();

    	for (json::iterator it = items.begin(), it_p = profiles.begin(); it != items.end(); ++it, ++it_p)
    	{
    		json item = it.value();
    		json profile = it_p.value();
    		if(item.find("last_message") == item.end())
    			continue;
    		VK::DialogInfo dialog;
    		if(dialog.parse(item, profile)) {

    			if (dialog.is_chat)
    			{
    				dialog.title += ": " + get_username(dialog.from_id);
    			}
                else
                {
	                dialog.title = get_username(dialog.chat_id);
                }
    			/*if(dialog.title.empty()) {
    				dialog.title = (dialog.is_chat) ?
                                get_chat_title(dialog.chat_id) : get_username(dialog.chat_id);
    			}*/

    			result.push_back(std::move(dialog));
    		}
    	}
	}
	
	return std::move(result);
}

VK::vector_dialogs VK::Messages::get_all_dialogs(const size_t max_count) {
    const size_t count = (max_count > 200 || max_count < 1) ? 200 : max_count;
    VK::vector_dialogs all_res, tmp_res;
    size_t offset = 0;
    for(;;) {
        tmp_res = this->get_dialogs(count, offset);
        if(tmp_res.size() < 1) {
            break;
        }
        std::move(tmp_res.begin(), tmp_res.end(), std::back_inserter(all_res));
        offset += count;
        if(max_count > 0 && max_count <= all_res.size()) {
            break;
        }
    }

    return std::move(all_res);
}

std::string VK::Messages::get_chat_title(const int chat_id) {


    if(chat_id < chat_offset) {
        return "";
    }
    VK::params_map params = {
        {"chat_ids", std::to_string(chat_id - chat_offset)},
    };

    json jres = call("messages.getChat", params);
    if(jres == nullptr || jres.find("error") != jres.end()) {
        return "";
    }
    json info = jres.at("response").get<json>();
    info = info.begin().value();
    string tmp = info.at("title").get<string>();
    return tmp;
}

std::string VK::Messages::get_username(const int user_id) {
    VK::params_map params = {
        {"user_ids", std::to_string(user_id)},
    };

    json jres = call("users.get", params);
    if(jres == nullptr || jres.find("error") != jres.end()) {
        return "";
    }
    VK::Attachment::User user;
    json info = jres.at("response").get<json>();
    if(info.begin() == info.end()) {
        return "";
    }
    info = info.begin().value();
    user.parse(info);
    return user.first_name + " " + user.last_name;
}

template<typename T>
std::vector<T> VK::Messages::get_attachments(const int chat_id, const size_t count) {
    std::vector<T> res;
    size_t real_count = (count > 200 || count < 1) ? 200 : count;
    string next;
    VK::params_map params = {
        {"peer_id", std::to_string(chat_id)},
        {"media_type", T::type},
        {"start_from", next},
        {"count", std::to_string(real_count)}
    };

    try {
        for(;;) {
            json jres = call("messages.getHistoryAttachments", params);
            if(jres == nullptr) {
                return std::move(res);
            }

            size_t parsed = 0;
            if(jres.find("error") == jres.end()) {

                next = jres.at("response").get<json>().at("next_from").get<string>();

                json items = jres.at("response").get<json>().at("items").get<json>();

                for (json::iterator it = items.begin(); it != items.end(); ++it) {
                    json item = it.value();
                    if(item.find("attachment") == item.end())
                        continue;
                    item = item.at("attachment").get<json>();
                    T att;
                    if(att.parse(item)) {
                        res.push_back(std::move(att));
                        parsed++;
                    }
                }
            }

            if((count == 0 && next.empty())
                    || (count > 0 && res.size() >= count)
                    || (parsed < 1)) {
                break;
            }

            params["start_from"] = next;

        }
    }
    catch(...) {

    }

    return std::move(res);
}


template std::vector<VK::Attachment::Audio>
VK::Messages::get_attachments<VK::Attachment::Audio>(const int , const size_t);

template std::vector<VK::Attachment::Photo>
VK::Messages::get_attachments<VK::Attachment::Photo>(const int , const size_t);

template std::vector<VK::Attachment::Document>
VK::Messages::get_attachments<VK::Attachment::Document>(const int , const size_t);

