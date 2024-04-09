from polygon import RESTClient
import environ

# Initialize environment and read API key
env = environ.Env()
environ.Env.read_env()

client = RESTClient(env('POLYGON_API_KEY'))

def fetch_options_contracts(symbol, limit=10):
    """
    Fetch options contracts for a given symbol and manually limit the output.

    :param symbol: Stock symbol to fetch options contracts for.
    :return: A limited list of options contracts.
    """
    
    contracts = []
    contracts_response = client.list_options_contracts(symbol, limit=limit)
    for contract in contracts_response:
        print(contract)
        contracts.append(contract)
    
    return contracts

def fetch_trades(symbol, start, end, limit=5):
    """
    :return: A list of trades.
    """
    trades = []
    trades_response = client.get_aggs(symbol, 4, "day", start, end)
    for trade in trades_response:
        trades.append(trade)

    return trades

#fetch_options_contracts("AAPL")

trades = fetch_trades("AAPL", "2024-04-04","2024-04-08")
for trade in trades:
    print(trade)