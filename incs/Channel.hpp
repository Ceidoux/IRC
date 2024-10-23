/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:11:32 by root              #+#    #+#             */
/*   Updated: 2024/09/30 19:59:35 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

# include "irc.h"

class Client;

class Channel
{
    public:
        Channel(std::string name);
        ~Channel();
        void    addClient(Client * added_client);
        void    addOperator(Client * added_operator);
        void    removeClient(Client * removed_client);
        void    banClient(Client * banned_client);
        void    addInvitedClient(Client * invited_client);
        void    removeOperator(Client * removed_operator);
        std::vector<Client *> getOperators();
        std::vector<Client *> getClients();
        std::vector<Client *> getInvitedClients();
        void    setTopic(std::string topic);
        void    setMode_i(bool status);
        void    setMode_t(bool status);
        void    setMode_k(bool status);
        void    setMode_o(bool status);
        void    setMode_l(bool status);
        void    setKey(std::string key);
        void    setUserLimit(std::string userLimit);
        std::string getName();
        std::string getTopic();
        bool    getMode_i();
        bool    getMode_t();
        bool    getMode_k();
        bool    getMode_o();
        bool    getMode_l();
        std::string    getKey();
        std::string    getUserLimit();
        std::size_t         getNumberOfClients( void ) const;
    private:
        Channel();
        std::vector<Client *> clients;
        std::vector<Client *> operators;
        std::vector<Client *> bannedClients;
        std::vector<Client *> invitedClients;
        std::string _name;
        std::string _topic;
        std::string _key;  
        std::string _userLimit;
        bool    mode_i;
        bool    mode_t;
        bool    mode_k;
        bool    mode_o;
        bool    mode_l;
};

#endif