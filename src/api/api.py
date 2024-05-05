from polygon import RESTClient
import environ
import requests
import pandas as pd
import numpy as np

# Initialize environment and read API key
env = environ.Env()
environ.Env.read_env()

API_KEY = env('POLYGON_API_KEY')

client = RESTClient(API_KEY)

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

def get_options_contract(symbol):
    """
    Fetch options contracts for a given symbol and manually limit the output.

    :param symbol: Stock symbol to fetch options contracts for.
    :return: A limited list of options contracts.
    """
    
   
    contracts_response = client.get_options_contract(symbol)
    print(contracts_response)
    return contracts_response

def fetch_trades(symbol, start, end):
    """
    :return: A list of trades.
    """
    trades = []
    trades_response = client.get_aggs(symbol, 4, "day", start, end)
    for trade in trades_response:
        trades.append(trade)

    return trades

def fetch_stock_data(ticker):
    url = f'https://api.polygon.io/v2/aggs/ticker/{ticker}/prev?apiKey={API_KEY}'
    response = requests.get(url)
    data = response.json()
    if 'results' in data and len(data['results']) > 0:
        return data['results'][0]['c']  # Return the last closing price
    else:
        return None

def fetch_historical_data(ticker):
    """Fetch historical daily data for a specified ticker"""
    url = f'https://api.polygon.io/v2/aggs/ticker/{ticker}/range/1/day/2023-01-01/2023-12-31?apiKey={API_KEY}'
    response = requests.get(url)
    data = response.json()
    if 'results' in data:
        return pd.DataFrame(data['results'])
    else:
        print("No data returned from API")
        return pd.DataFrame()

def calculate_yearly_volatility(ticker):
    """Calculate and return the annualized volatility of the stock based on daily closing prices."""
    df = fetch_historical_data(ticker)
    if not df.empty:
        df['date'] = pd.to_datetime(df['t'], unit='ms')  # Convert timestamp to date
        df.set_index('date', inplace=True)
        df['returns'] = np.log(df['c'] / df['c'].shift(1))  # Calculate daily returns
        daily_volatility = df['returns'].std()  # Standard deviation of daily returns
        annualized_volatility = daily_volatility * np.sqrt(252)  # Scale to annual volatility
        print(f"The annualized volatility for {ticker} is: {annualized_volatility:.2%}")
        return annualized_volatility
    else:
        return None

def fetch_recent_data(ticker, num_days):
    """Fetch the last 'num_days' of daily data for a specified ticker using Polygon.io API."""
    url = f'https://api.polygon.io/v2/aggs/ticker/{ticker}/range/1/day/2023-01-01/2023-12-31?apiKey={API_KEY}&limit={num_days}'
    response = requests.get(url)
    data = response.json()
    if 'results' in data:
        return pd.DataFrame(data['results'])
    else:
        print("No data returned from API")
        return pd.DataFrame()

def calculate_volatility(ticker, num_days, label):
    """Calculate and return the volatility for a specified number of days."""
    df = fetch_recent_data(ticker, num_days)
    if not df.empty:
        df['date'] = pd.to_datetime(df['t'], unit='ms')  # Convert timestamp to date
        df.set_index('date', inplace=True)
        # split into a diff function like calc_returns where we pass in a dataframe
        # we should name our calculation 


        # create a scale to annual volatility function 
        df['returns'] = np.log(df['c'] / df['c'].shift(1))  # Calculate daily returns
        daily_volatility = df['returns'].std()  # Standard deviation of daily returns
        annualized_volatility = daily_volatility * np.sqrt(252)  # Scale to annual volatility
        print(f"The {label} volatility for {ticker} is: {annualized_volatility:.2%}")
        return annualized_volatility
    else:
        return None
        
def main():
    #fetch_options_contracts("AAPL")
    
    #get_options_contract("O:AAPL240412C00170000")

    # trades = fetch_trades("AAPL", "2023-04-04","2024-04-08")
    # for trade in trades:
    #     print(trade)
    #print(fetch_stock_data("AAPL"))

    calculate_yearly_volatility("AAPL")
    calculate_volatility("AAPL", 5, "5-day")
    calculate_volatility("AAPL", 20, "monthly")


if __name__ == "__main__":
    main()