from flask import Flask, g, render_template, request
import sqlite3
import datetime

app = Flask(__name__)
DATABASE = 'database.db'

def get_db():
    db = getattr(g, '_database', None)
    if db is None:
        db = g._database = sqlite3.connect(DATABASE)
    return db

@app.teardown_appcontext
def close_connection(exception):
    db = getattr(g, '_database', None)
    if db is not None:
        db.close()

@app.route('/')
def index():
    conn = get_db()
    cursor = conn.cursor()

    # Create the 'events' table if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS events
                    (id INTEGER PRIMARY KEY AUTOINCREMENT,
                    ime TEXT NOT NULL,
                    datum TIMESTAMP NOT NULL,
                    ura TIMESTAMP NOT NULL,
                    opis TEXT NOT NULL,
                    pogoj TEXT NOT NULL,
                    nagrada TEXT NOT NULL,
                    ogranizator TEXT NOT NULL,
                    lokacija TEXT NOT NULL)''')

    cursor.execute("SELECT * FROM events ORDER BY datum DESC")
    data = cursor.fetchall()
    return render_template("index.html", events=data)

@app.route("/login", methods=["GET", "POST"])
def login():
    return render_template("login.html")

@app.route("/ableEdit", methods=["GET", "POST"])
def editevent():
    if request.method == "POST":
        usernameget = request.form.get("username")
        passwordget = request.form.get("password")
        current_time = datetime.datetime.now().time()
        password = current_time.strftime("%H%M")
        if passwordget == password and usernameget == "ALI":
            data = selectAll()
            return render_template("editevent.html", events=data)
        else:
            return render_template("login.html")

def selectAll():
    # Retrieve all events from the table
    conn = get_db()
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM events ORDER BY datum DESC")
    data = cursor.fetchall()
    return data

@app.route("/addEvent", methods=["GET", "POST"])
def addEvent():
    if request.method == "POST":
        conn = get_db()
        cursor = conn.cursor()

        # Assuming you have the necessary data for the event
        ime = request.form.get("ime")
        datum = request.form.get("datum")
        ura = request.form.get("ura")
        opis = request.form.get("opis")
        pogoj = request.form.get("pogoj")
        nagrada = request.form.get("nagrada")
        ogranizator = request.form.get("ogranizator")
        lokacija = request.form.get("lokacija")

        event_data = {
            'ime': ime,
            'datum': datum,
            'ura': ura,
            'opis': opis,
            'pogoj': pogoj,
            'nagrada': nagrada,
            'ogranizator': ogranizator,
            'lokacija': lokacija
        }

        # Insert the event into the table
        cursor.execute('''INSERT INTO events (ime, datum, ura, opis, pogoj, nagrada, ogranizator, lokacija)
                  VALUES (?, ?, ?, ?, ?, ?, ?, ?)''',
               (event_data['ime'], event_data['datum'], event_data['ura'],
                event_data['opis'], event_data['pogoj'], event_data['nagrada'],
                event_data['ogranizator'], event_data['lokacija']))

        # Commit the changes to the database
        conn.commit()
        data = selectAll()
        # Pass the event data to the template
        return render_template("editevent.html", events=data)

@app.route("/deleteEvent", methods=["GET", "POST"])
def deleteEvent():
    if request.method == "POST":
        conn = get_db()
        cursor = conn.cursor()
        id = request.form.get("id")
        cursor.execute("DELETE FROM events WHERE id = ?", (id,))
        conn.commit()
        data = selectAll()
        return render_template("editevent.html", events=data)

if __name__ == '__main__':
    app.debug = True
    app.run()