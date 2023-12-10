#include "core.h"
#include "trie.h"

void demoHandler(const HttpRequest &request, HttpResponse &response)
{
    auto name = request.query("name");
    response.setStatusCode(200);

    response.setHeader("Content-Type", "application/json");

    auto jsonStr = R"({"name" : "lsm" })";
    response.write(jsonStr, strlen(jsonStr));
}

void init(TinyHttpServer &server)
{
    server.addRoute("demo", demoHandler);
    server.addRoute("find", demoHandler);
    server.addRoute("GET", "find/:id", [](const HttpRequest &request, HttpResponse &response)
    {
        std::cout << request.param("id") << std::endl;
        auto jsonStr = std::string(R"({"id" : ")");
        jsonStr = jsonStr + request.param("id") + R"("})";
        response.setHeader("Content-Type", "application/json");
        response.write(jsonStr.c_str(), jsonStr.size());
    });
    server.addRoute("test500", [](const HttpRequest &request, HttpResponse &response)
    {
        response.setStatusCode(500);
    });
}

int main()
{
    TinyHttpServer server;
    server.setBlock(true);
    server.setHost("127.0.0.1");
    server.setPort(9999);
    init(server);
    server.run();
    return 0;
}
