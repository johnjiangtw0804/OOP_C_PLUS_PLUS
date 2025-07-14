#include <iostream>
#include <optional>

using namespace std;

struct PaymentResult{
    bool isSuccessful;
    optional<string> message;
    optional<int> transactionID;
};

enum class PaymentType {
    CREDIT_CARD,
    PAYPAL,
    CRYPTO
};

// product
class IPaymentProcessor
{
public:
    virtual PaymentResult paymentProcess() = 0;
    virtual ~IPaymentProcessor() = default; // for polymorphism
};

class CreditCardPayment : public IPaymentProcessor{
public:
    PaymentResult paymentProcess() override
    {
        return PaymentResult{true, "Pay by credit card", 0};
    }
};

class CryptoPayment : public IPaymentProcessor
{
public:
    PaymentResult paymentProcess() override
    {
        return PaymentResult{true, "Pay by crypto", 1};
    }
};

class PaypalPayment : public IPaymentProcessor
{
public:
    PaymentResult paymentProcess() override
    {
        return PaymentResult{true, "Pay by paypal", 2};
    }
};
// Simple factory: 一個方法，靠者 enum or parameters 去區隔
// factory method: 需要 interface 去讓各個 subclass 去實作 createProduct()
// abstract factory: 一個大工廠，去實作一整組, paymentProcessor, refundProcessor...
class PaymentFactory
{
public:
    unique_ptr<IPaymentProcessor> createPaymentProcessor(PaymentType type)
    {
        switch (type) {
            case PaymentType::CREDIT_CARD:
                return make_unique<CreditCardPayment>();
            case PaymentType::CRYPTO:
                return make_unique<CryptoPayment>();
            case PaymentType::PAYPAL:
                return make_unique<PaypalPayment>();
            default:
                return nullptr;
        }
    }
};

int main() {
    // create payment processor
    unique_ptr<PaymentFactory> factory = make_unique<PaymentFactory>();
    unique_ptr<IPaymentProcessor> paymentProcessor = factory->createPaymentProcessor(PaymentType::CREDIT_CARD);

    auto res = paymentProcessor->paymentProcess();
    if (res.message.has_value()) {
        cout << res.message.value() << endl;
    }
}
