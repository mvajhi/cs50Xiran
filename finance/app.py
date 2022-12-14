from datetime import datetime
from operator import iconcat
import os
import re
import string

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, jsonify
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd


# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

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
    cash = db.execute("SELECT cash FROM users WHERE id = ?",
                      session["user_id"])[0]["cash"]

    finances = (db.execute("SELECT * FROM finance WHERE users_id = ?",
                session["user_id"]), session["user_id"])[0]

    finances_with_value = []
    investments = float(0)

    for finance in finances:
        if not finance["amount"] == 0:
            price = lookup(finance["symbole"])["price"]
            total_price = price * finance["amount"]

            investments += total_price

            finance["value"] = usd(total_price)
            finance.pop("id")
            finance.pop("users_id")

            finances_with_value.append(finance)

    total_finance = cash + investments
    return render_template("index.html", finances=finances_with_value, investments=usd(investments), cash=usd(cash), total_finance=usd(total_finance))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbole = request.form.get("symbol").upper()
        try:
            amount = int(request.form.get("shares"))
        except:
            return apology("Invalid amount")
        if amount <= 0 or not isinstance(amount, int):
            return apology("Invalid amount")

        info_symbole = lookup(symbole)
        if info_symbole == None:
            return apology("symbole not found")

        price = float(info_symbole["price"])
        total_price = price * amount
        user_cash = db.execute(
            "SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        if user_cash < total_price:
            return apology("You don't have enough money")

        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   (user_cash - total_price), session["user_id"])
        db.execute("INSERT INTO history (users_id, symbole, amount, price, total_price, type, date) VALUES (?, ?, ?, ?, ?, ?, ?)",
                   session["user_id"], symbole, amount, price, total_price, "buy", datetime.now())

        if db.execute("SELECT * FROM finance WHERE symbole = ?", symbole) == []:
            db.execute("INSERT INTO finance (users_id, symbole, amount) VALUES (?, ?, ?)",
                       session["user_id"], symbole, amount)
        else:
            db.execute(
                "UPDATE finance SET amount = amount + ? WHERE symbole = ?", amount, symbole)

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute(
        "SELECT symbole, amount, price, total_price, type, date FROM history WHERE users_id = ?", session["user_id"])

    i = int(0)
    history_with_counter = []
    for history_part in history:
        i += 1
        history_part["counter"] = i
        history_with_counter.append(history_part)

    return render_template("history.html", history=history_with_counter)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

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
    """Get stock quote."""
    if request.method == "POST":
        try:
            quote = request.form.get("symbol").upper()
        except:
            return apology("invalid input")

        if quote:
            symbole = lookup(quote)
            if symbole == None:
                return apology("Not Found")
            else:
                name = symbole["name"]
                price = usd(symbole["price"])
                symbole_val = symbole["symbol"]

                return render_template("quoted.html", name=name, price=price, symbole_val=symbole_val)

        else:
            return apology("No input found")

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # get input
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # check input and save them
        if not username == "" and not password == "" and password == confirmation and db.execute("SELECT * FROM users WHERE username = ?", username) == []:
            hashval = generate_password_hash(password)
            db.execute(
                "INSERT INTO users (username, hash) VALUES(?, ?)", username, hashval)
            return redirect("/")

        else:
            return apology("try again")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbole = request.form.get("symbol").upper()
        try:
            amount = int(request.form.get("shares"))
        except:
            return apology("Invalid amount")
        if amount <= 0 or not isinstance(amount, int):
            return apology("Invalid amount")

        info_symbole = lookup(symbole)
        if info_symbole == None:
            return apology("symbole not found")

        price = float(info_symbole["price"])
        total_price = price * amount
        user_amount = db.execute(
            "SELECT amount FROM finance WHERE symbole = ?", symbole)[0]["amount"]

        try:
            if user_amount < amount:
                return apology("You don't have enough stock")
        except:
            return apology("You don't have enough stock")

        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?",
                   total_price, session["user_id"])
        db.execute("INSERT INTO history (users_id, symbole, amount, price, total_price, type, date) VALUES (?, ?, ?, ?, ?, ?, ?)",
                   session["user_id"], symbole, amount, price, total_price, "sell", datetime.now())

        db.execute(
            "UPDATE finance SET amount = amount - ? WHERE symbole = ?", amount, symbole)

        return redirect("/")

    else:
        symboles = db.execute(
            "SELECT symbole FROM finance WHERE users_id = ?", session["user_id"])
        symboles_val = []
        for symbole in symboles:
            symbole_val = symbole["symbole"]
            symboles_val.append(symbole_val)
        return render_template("sell.html", symboles=symboles_val)
