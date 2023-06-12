import os
import re
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Initialize variables to hold portfolio and total value
    portfolio = {}
    total_value = 0

    rows = db.execute("SELECT * from transactions WHERE user_id = ?", session["user_id"])

    # Iterate through each transaction and update the portfolio dictionary
    for row in rows:
        symbol = row["symbol"]
        shares = row["shares"]
        price = lookup(symbol)

        # Calculate total value of each holding
        value = shares * price["price"]
        total_value += value

        # Update portfolio dictionary with new data
        if symbol in portfolio:
            portfolio[symbol]["shares"] += shares
            portfolio[symbol]["total"] += value
        else:
            portfolio[symbol] = {
                "symbol": symbol,
                "shares": shares,
                "total": value
            }

    # Convert portfolio dictionary back to list of dictionaries for template rendering
    portfolio = list(portfolio.values())

    # Retrieve user's current cash balance from users table
    result = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = result[0]["cash"]

    # Calculate grand total
    grand_total = float(cash) + total_value

    # Render template with portfolio and total information
    return render_template("index.html", portfolio=portfolio, cash=cash, total_value=total_value, grand_total=grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # Get symbol and shares from form
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Check for input errors
        if not symbol:
            return apology("Please enter a stock symbol")
        if not shares or not shares.isdigit() or int(shares) < 1:
            return apology("Please enter a positive integer for shares")

        # Look up the stock symbol
        stock = lookup(symbol)
        if not stock:
            return apology("Invalid stock symbol")

        # Calculate the total cost of the shares
        price = stock['price']
        total_cost = price * int(shares)

        # Get the user's current cash balance
        rows = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        if len(rows) != 1:
            return apology("Internal server error")
        cash = rows[0]["cash"]

        # Check if user has enough cash to buy shares
        if cash < total_cost:
            return apology("Insufficient funds")

        # Add transaction to database
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, transacted_at) VALUES (?, ?, ?, ?, datetime('now'))",
                   session["user_id"], symbol, shares, -total_cost)

        # Update user's cash balance
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - total_cost, session["user_id"])

        # Display success message
        flash(f"Bought {shares} share(s) of {stock['name']} ({symbol}) for {usd(price)} each")

        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Initialize variables to hold portfolio and total value
    portfolio = []
    total_value = 0

    rows = db.execute("SELECT * from transactions WHERE user_id = ?", session["user_id"])

    for row in rows:
        symbol = row["symbol"]
        shares = row["shares"]
        price = lookup(symbol)

        # Calculate total value of each holding
        value = shares * price["price"]
        total_value += value

        # Add stock information to portfolio list

        portfolio.append({
            "symbol": symbol,
            "shares": shares,
            "total": value
        })

    # Retrieve user's current cash balance from users table
    result = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = result[0]["cash"]

    # Calculate grand total
    grand_total = float(cash) + total_value

    # Render template with portfolio and total information
    return render_template("history.html", portfolio=portfolio, cash=cash, total_value=total_value, grand_total=grand_total)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == 'POST':
        """Get stock quote."""
        symbol = request.form.get("symbol")
        if not symbol or symbol == "'" or symbol == ";":
            return apology("quote input", 400)
        data = lookup(symbol)
        if data:
            return render_template("quoted.html", data=data)
        else:
            return apology("quote input", 400)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == 'POST':
        # Validate submission
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        if not username or not password or not confirmation or password != confirmation or len(rows) != 0 or len(password) < 5:
            return apology("Input is invalid", 400)

        # Remember registrant
        passwordHash = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, passwordHash)
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        # Get symbol and shares from form
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Check for input errors
        if not symbol:
            return apology("Please enter a stock symbol")
        if not shares or not shares.isdigit() or int(shares) < 1:
            return apology("Please enter a positive integer for shares")

        # Get the user's current cash balance
        sql = db.execute("SELECT SUM(shares) as total FROM transactions WHERE user_id = ? and symbol = ?",
                         session["user_id"], symbol)
        total_shares = sql[0]["total"] if sql[0]["total"] else 0
        if total_shares <= int(shares):
            return apology("You don't have enough shares to sell")

        # Calculate the total cost of the shares
        price = lookup(symbol)
        total_cost = price['price'] * int(shares)

        # Add transaction to database
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, transacted_at) VALUES (?, ?, ?, ?, datetime('now'))",
                   session["user_id"], symbol, -int(shares), price['price'])

        # Update user's cash balance
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", total_cost, session["user_id"])

        # Display success message
        stock = lookup(symbol)
        flash(f"Sold {shares} share(s) of {stock['name']} ({symbol}) for ${usd(stock['price'])} each")

        return redirect("/")
    else:
        symbols = db.execute("""SELECT symbol, sum(shares) as sum_of_shares FROM transactions
                                  WHERE user_id = ? GROUP BY user_id, symbol
                                  HAVING sum_of_shares > 0;""", session["user_id"])
        return render_template("sell.html", symbols=symbols)

