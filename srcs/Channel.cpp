/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smestre <smestre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:17:38 by root              #+#    #+#             */
/*   Updated: 2024/09/30 19:35:49 by smestre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

/* CONSTRUCTOR AND DESTRUCTOR */

Channel::Channel(std::string name) : _name(name), _userLimit(""), mode_i(false), mode_t(true), mode_k(false), mode_o(true), mode_l(false) { } 

Channel::~Channel() { }

/* OTHER FUNCTIONS */

void    Channel::addClient(Client * added_client)
{
    if (std::find(this->clients.begin(), this->clients.end(), added_client) == this->clients.end())
        this->clients.push_back(added_client);
    else
        std::cout << "Client already in channel" << std::endl;
    std::cout << "Nb of clients: " << this->getNumberOfClients() << std::endl;
}

void    Channel::removeClient(Client * removed_client)
{
    if (std::find(this->clients.begin(), this->clients.end(), removed_client) != this->clients.end())
    {   
        this->removeOperator(removed_client);
        this->clients.erase(std::remove(this->clients.begin(), this->clients.end(), removed_client), this->clients.end());
    }
    else
        std::cout << "Client not in channel" << std::endl;
    std::cout << "Nb of clients: " << this->getNumberOfClients() << std::endl;
}

void    Channel::removeOperator(Client * removed_operator)
{
    if (std::find(this->operators.begin(), this->operators.end(), removed_operator) != this->operators.end())
        this->operators.erase(std::remove(this->operators.begin(), this->operators.end(), removed_operator), this->operators.end());
    else
        std::cout << "Client not an operator" << std::endl;
}

void    Channel::banClient(Client * banned_client)
{
    if (std::find(this->clients.begin(), this->clients.end(), banned_client) != this->clients.end())
    {
        this->bannedClients.push_back(banned_client);
        if (std::find(this->clients.begin(), this->clients.end(), banned_client) != this->clients.end())
            this->removeClient(banned_client);
    }
    else
        std::cout << "Client not in channel" << std::endl;
}

void    Channel::addOperator(Client * added_operator)
{
    if (std::find(this->operators.begin(), this->operators.end(), added_operator) == this->operators.end())
        this->operators.push_back(added_operator);
    else
        std::cout << "Client already an operator" << std::endl;
}

void    Channel::addInvitedClient(Client * invited_client)
{
    if (std::find(this->invitedClients.begin(), this->invitedClients.end(), invited_client) == this->invitedClients.end())
        this->invitedClients.push_back(invited_client);
    else
        std::cout << "Client already invited" << std::endl;
}

/* GETTERS & SETTERS */

std::vector<Client * > Channel::getClients()
{
    return this->clients;
}

std::vector<Client *> Channel::getInvitedClients()
{
    return this->invitedClients;
}

std::vector<Client *> Channel::getOperators()
{
    return (this->operators);
}

std::string Channel::getTopic()
{
    return this->_topic;
}

void Channel::setTopic(std::string topic)
{
    this->_topic = topic;
    return ;
}


std::string Channel::getName()
{
    return this->_name;
}

void    Channel::setMode_i(bool status)
{
    this->mode_i = status;
}

void      Channel::setMode_t(bool status)
{
    this->mode_t = status;
}

void      Channel::setMode_k(bool status)
{
    this->mode_k = status;
}
void      Channel::setMode_o(bool status)
{
    this->mode_o = status;
}
void      Channel::setMode_l(bool status)
{
    this->mode_l = status;
}

void      Channel::setKey(std::string key)
{
    this->_key = key;
}

void    Channel::setUserLimit(std::string userLimit)
{
    this->_userLimit = userLimit;
}

bool    Channel::getMode_i()
{
    return this->mode_i;
}

bool    Channel::getMode_t()
{
    return this->mode_t;
}

bool    Channel::getMode_k()
{
    return this->mode_k;
}

bool    Channel::getMode_o()
{
    return this->mode_o;
}

bool    Channel::getMode_l()
{
    return this->mode_l;
}

std::string    Channel::getKey()
{
    return this->_key;
}

std::string            Channel::getUserLimit()
{
    return this->_userLimit;
}

size_t     Channel::getNumberOfClients( void ) const
{
    return this->clients.size();
}
