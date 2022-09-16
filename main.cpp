#include <iostream>
#include <array>
#include "lib/json.hpp" // allows for JSON parsing
#include "lib/cpp-httplib.hpp" // allows for HTTP requests

// makes life easier by removing how much needs to be typed
using namespace std;
using json = nlohmann::json;

/**
 * Sends a GET request to a domain, with the uri attached
 * @param domain
 * @param uri
 * @return json - the data received from the server
 */
json get(const string &domain, const string &uri) {
    // Set up an HTTP client
    auto client = httplib::Client(domain);
    // return a parsed json object of the return request
    return json::parse(client.Get(uri)->body);
}

/**
 * Converts the amount in one currency to CAD
 * @param currency the currency type CAD, EUR, etc.
 * @param in
 * @return double - the money that converted
 */
double convert(const string &currency, double in) {
    // don't send anything invalid to the API
    if (in <= 0) return 0;

    /*
     * Calls the API with the data required to convert
     * http://api.exchangerate.host/convert?from={CURRENCY}&to=CAD&amount={AMOUNT}
     */
    return get("http://api.exchangerate.host",
               "/convert?"
               "from=" + currency +
               "&to=CAD&amount=" + to_string(in))["result"];
}

int main() {
    // a Look-Up Table (LUT) for the different available currencies
    const array<string, 10> currencies = {"EUR", "RUB", "SGD", "PHP", "MXN", "INR", "JPY", "EGP", "KRW", "JMD"};
    double total = 0; // The total

    float x; //  reusing variables is better for memory

    // loops through the different types of currencies
    for (const auto &currency: currencies) {
        // asks for prompt
        cout << "Enter amount in " << currency << ":";
        cout.flush(); // compatibility with most terminals, because no use endl
        cin >> x; // get input
        total += convert(currency, x); // convert and add to total
    }

    // print the output rounded to 2 decimals
    cout << fixed << setprecision(2) << "Total in CAD: $" << total << endl;

    return 0;
}
