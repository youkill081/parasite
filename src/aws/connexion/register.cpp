/*
** EPITECH PROJECT, 2023
** aze
** File description:
** eza
*/

#include "rbb_aws/aws_manager.hpp"
#include "aws/cognito-idp/model/SignUpRequest.h"

#include <thread>

using namespace rbb_aws;

void *aws_manager::running_register(std::string mail, std::string password, std::string birthdate)
{
    std::cout << "register new user" << std::endl;

    Aws::CognitoIdentityProvider::Model::SignUpRequest request;

    request.SetClientId("f0qjogfmg8mgj8klpt7mp1vqq"); //user pool

    request.AddUserAttributes(Aws::CognitoIdentityProvider::Model::AttributeType().WithName("email").WithValue(mail));
    request.AddUserAttributes(Aws::CognitoIdentityProvider::Model::AttributeType().WithName("birthdate").WithValue(birthdate));
    request.SetUsername(mail.substr(0, mail.find('@')));
    request.SetPassword(password);

    Aws::CognitoIdentityProvider::Model::SignUpOutcome outcome = this->cognito_client->SignUp(request);

    if (outcome.IsSuccess()) {
        std::cout << "register success" << std::endl;
    } else {
        std::cout << outcome.GetError().GetMessage() << std::endl;
    }
    return NULL;
}

int aws_manager::start_register_user(std::string mail, std::string password, std::string birthdate)
{
    printf("ici\n");
    if (not this->is_init) {
        std::cout << "error: aws is not init" << std::endl;
        return false;
    }
    this->working_thread = new std::future<void *>;
    *this->working_thread = std::async(&aws_manager::running_register, this, mail, password, birthdate);
    printf("le thread est crée\n");
    return true;
}
