/*
** EPITECH PROJECT, 2023
** aze
** File description:
** eza
*/

#include <thread>

#include <aws/core/auth/AWSCredentialsProvider.h>
#include "rbb_aws/aws_manager.hpp"

using namespace rbb_aws;

void aws_manager::create_manager(void)
{
    this->credential = new Aws::Auth::AWSCredentials("HIDE", "HIDE");

    this->client = new Aws::Client::ClientConfiguration;
    this->client->region = "eu-west-3";

    try {
        this->SES_client = new Aws::SESV2::SESV2Client(*this->credential, *this->client);
    } catch(...) {
        std::cout << "Error while creating the SES client" << std::endl;
    }
    
    std::cout << "end of aws creation !" << std::endl;
    this->is_init = true;
}

aws_manager::aws_manager()
{
    Aws::InitAPI(this->option);
    std::cout << "creating aws initialisation thread" << std::endl;
    this->init_thread = std::async(&aws_manager::create_manager, this);
}

void aws_manager::stop(void)
{
    Aws::ShutdownAPI(this->option);
    
    delete this->credential;
    delete this->client;
}
