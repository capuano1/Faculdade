import pytest
from unittest.mock import patch
from process_payment import process_payment, InvalidPaymentDetails, PaymentGatewayError

def random_fail():
    return 0.1

def random_success():
    return 0.9

def test_valid_payment_std_currency():
    with patch('random.random', random_success):
        assert process_payment(10, 500)["status"] == "success"

def test_valid_payment_usd():
    with patch('random.random', random_success):
        assert process_payment(10, 500, "USD")["status"] == "success"

def test_valid_payment_eur():
    with patch('random.random', random_success):
        assert process_payment(10, 500, "EUR")["status"] == "success"

def test_valid_payment_jpy():
    with patch('random.random', random_success):
        assert process_payment(10, 500, "JPY")["status"] == "success"

def test_invalid_user_id():
    with pytest.raises(InvalidPaymentDetails):
        process_payment(None, 500)

def test_invalid_amount():
    with pytest.raises(InvalidPaymentDetails):
        process_payment(10, -1)

def test_invalid_currency():
    with pytest.raises(InvalidPaymentDetails):
        process_payment(10, 500, "BRL")

def test_too_many_retries():
    with pytest.raises(PaymentGatewayError), patch('random.random', random_fail):
        process_payment(10, 500, "USD")