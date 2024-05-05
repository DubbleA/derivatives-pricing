from dotenv import load_dotenv
import os

# Load environment variables from .env file
load_dotenv()

# Access your variables
API_KEY = os.getenv('POLYGON_API_KEY')
import requests
import pandas as pd
import numpy as np
from polygon import RESTClient
import csp
from datetime import datetime

client = RESTClient(API_KEY)

def fetch_stock_data(ticker):
    try:
        url = f'https://api.polygon.io/v2/aggs/ticker/{ticker}/prev?apiKey={API_KEY}'
        response = requests.get(url)
        data = response.json()
        if 'results' in data and len(data['results']) > 0:
            return data['results'][0]['c']  # Return the last closing price
    except Exception as e:
        print(f"Failed to fetch stock data: {e}")
    return None

@csp.node
def spread(bid: csp.ts[float], ask: csp.ts[float]) -> csp.ts[float]:
    if csp.valid(bid, ask):
        return ask - bid

@csp.graph
def my_graph():
    bid = csp.const(1.0)
    ask = csp.const(2.0)
    bid = csp.multiply(bid, csp.const(4))
    ask = csp.multiply(ask, csp.const(3))
    s = spread(bid, ask)
    csp.print('spread', s)
    csp.print('bid', bid)
    csp.print('ask', ask)

if __name__ == '__main__':
    print(fetch_stock_data("AAPL"))
    csp.run(my_graph, starttime=datetime.utcnow())
    csp.show_graph(my_graph) 
