import speech_recognition as sr
import requests
import time

# ─── CONFIG ───────────────────────────────────────────────
BLYNK_TOKEN = "1hqcKqiVXF0-fWrJ-rbCNlSrPbo7kwNz"
COOLDOWN    = 3   # seconds between commands
# ──────────────────────────────────────────────────────────

BLYNK_SERVERS = [
    "sgp1.blynk.cloud",   # Singapore (closest for India)
    "fra1.blynk.cloud",   # Frankfurt
    "ny3.blynk.cloud",    # New York
    "lon1.blynk.cloud",   # London
    "ams3.blynk.cloud",   # Amsterdam
    "blynk.cloud",        # Global fallback
]

def find_blynk_server():
    """Try each server and return the first one that accepts the token."""
    print("[INIT] Finding your Blynk server...")
    for server in BLYNK_SERVERS:
        try:
            url = f"https://{server}/external/api/get"
            r = requests.get(url, params={"token": BLYNK_TOKEN, "V0": ""}, timeout=5)
            if r.status_code != 404 and "Invalid token" not in r.text and "No token" not in r.text:
                print(f"[INIT] Connected to: {server}")
                return server
        except Exception:
            pass
    return None

BLYNK_SERVER = None

def send_blynk(value):
    """Write to V0: 255 = Fan ON, 0 = Fan OFF"""
    global BLYNK_SERVER
    if BLYNK_SERVER is None:
        print("[ERROR] No Blynk server found. Check your token and internet.")
        return
    try:
        url = f"https://{BLYNK_SERVER}/external/api/update"
        r = requests.get(url, params={"token": BLYNK_TOKEN, "V0": value}, timeout=5)
        if r.status_code == 200:
            state = "ON" if value == 255 else "OFF"
            print(f"[SENT] Fan {state} → {BLYNK_SERVER} V0={value}")
        else:
            print(f"[ERROR] Blynk: {r.status_code} — {r.text.strip()}")
    except requests.exceptions.ConnectionError:
        print("[ERROR] No internet connection")
    except requests.exceptions.Timeout:
        print("[ERROR] Blynk request timed out")

def listen_for_command(recognizer, microphone):
    with microphone as source:
        print("\n[LISTENING] Say 'AC ON' or 'AC OFF'...")
        recognizer.adjust_for_ambient_noise(source, duration=0.5)
        try:
            audio = recognizer.listen(source, timeout=5, phrase_time_limit=4)
        except sr.WaitTimeoutError:
            return None
    try:
        text = recognizer.recognize_google(audio).lower().strip()
        print(f"[HEARD] {text}")
        return text
    except sr.UnknownValueError:
        print("[NOISE] Could not understand audio")
        return None
    except sr.RequestError:
        print("[ERROR] Google Speech API unavailable. Check internet.")
        return None

def main():
    global BLYNK_SERVER
    BLYNK_SERVER = find_blynk_server()
    if BLYNK_SERVER is None:
        print("[FATAL] Could not connect to any Blynk server. Check token and internet.")
        return

    recognizer = sr.Recognizer()
    microphone = sr.Microphone()

    print("=== Smart AC Voice Controller (Blynk) ===")
    print("Commands: 'AC ON'  |  'AC OFF'")
    print("Press Ctrl+C to stop\n")

    last_command_time = 0

    while True:
        text = listen_for_command(recognizer, microphone)
        if text is None:
            continue

        now = time.time()
        if now - last_command_time < COOLDOWN:
            print(f"[COOLDOWN] Wait {COOLDOWN}s between commands")
            continue

        if "ac on" in text:
            send_blynk(255)
            print("[ACTION] AC ON command sent!")
            last_command_time = now

        elif "ac off" in text:
            send_blynk(0)
            print("[ACTION] AC OFF command sent!")
            last_command_time = now

        else:
            print("[IGNORED] Not a valid command")

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\n[STOPPED] Voice controller stopped.")
