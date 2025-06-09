// TestGrpc.cpp: 定义应用程序的入口点。
//
#include<string>
#include "TestGrpc.h"
#include"gen/example.grpc.pb.h"
#include"gen/example.pb.h"
#include<grpcpp/grpcpp.h>
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using volo::example::ItemService;
using volo::example::GetItemRequest;
using volo::example::GetItemResponse;
class ItemClient {
public:
    ItemClient(std::shared_ptr<Channel> channel)
        : stub_(ItemService::NewStub(channel)) {
    }

    void GetItem(int64_t id) {
        GetItemRequest request;
        request.set_id(id);
        GetItemResponse response;
        ClientContext context;

        Status status = stub_->GetItem(&context, request, &response);
        if (status.ok()) {
            const auto& item = response.item();
            std::cout << "Item ID: " << item.id() << std::endl;
            std::cout << "Item Title: " << item.title() << std::endl;
			std::cout << "Item content: " << item.content() << std::endl;
            for (const auto& [key, value] : item.extra()) {
                std::cout << "Extra[" << key << "] = " << value << "\n";
            }
        }
        else {
            std::cerr << "rpc filed, error code: " << status.error_code()
                << ", message: " << status.error_message() << std::endl;
        }
    }

private:
    std::unique_ptr<ItemService::Stub> stub_;
};

int main(){
    ItemClient client(grpc::CreateChannel("localhost:8080", grpc::InsecureChannelCredentials()));
    client.GetItem(1); // 请求 ID 为 1 的 item
    return 0;
}
