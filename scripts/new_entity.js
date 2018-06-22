'use strict'

const fs = require('fs');
const path = require('path');

function parseArgs() {
    const params = {};
    const args = process.argv;

    if (args.length < 3) {
        // Handle failure case
    }

    params.entityName = args[2];
    params.headerGuard = args[2].toUpperCase() + "_H_INCLUDED";

    return params;
}

function makeHeader(args) {
    const headerFile = 
`#ifndef ${args.headerGuard}
#define ${args.headerGuard}

#include "Entity.h"

class ${args.entityName} : public Entity
{
public:
    ${args.entityName}(unsigned int id, std::string name, std::vector<std::string> params);
    ~${args.entityName}();

    void initParameters(std::vector<std::string> params);
    void update(float dt);
    std::string getEntityDescription();
    EntityType getEntityType();
    void handleEntityCollision(Entity* other);

private:
};

#endif
`;

    return headerFile;
}

function makeCpp(args) {
    const cppFile =
`#include "${args.entityName}.h"

${args.entityName}::${args.entityName}(unsigned int id, std::string name, std::vector<std::string> params) :
    Entity(id, name, params)
{

}

${args.entityName}::~${args.entityName}()
{

}

void ${args.entityName}::initParameters(std::vector<std::string> params)
{
    Entity::initParameters(params);

    for (auto it : params)
    {
        auto key = it.substr(0, it.find(" "));
        auto value = it.substr(it.find(" ") + 1);
    }
}

EntityType ${args.entityName}::getEntityType()
{
    //fixme;
}

std::string ${args.entityName}::getEntityDescription()
{
    return std::to_string(id) + " ${args.entityName} " + name + "\\n"
        + getCommonParameters();
}

void ${args.entityName}::update(float dt)
{
    Entity::update(dt);
}

void ${args.entityName}::handleEntityCollision(Entity *other)
{
    switch (other->getEntityType())
    {
    default:
        break;
    }
}
`;
    return cppFile;
}

(() => {
    const args = parseArgs();
    const header = makeHeader(args);
    const cpp = makeCpp(args);

    fs.writeFileSync(path.join(__dirname, "..", "src", `${args.entityName}.h`), header);
    fs.writeFileSync(path.join(__dirname, "..", "src", `${args.entityName}.cpp`), cpp);
})();