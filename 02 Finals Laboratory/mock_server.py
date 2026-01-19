from fastapi import FastAPI
import uvicorn

app = FastAPI()

@app.get("/led/group/{number}/toggle")
def toggle(number: str):
    print(f">>> Server received toggle request for Group: {number}")
    return {"status": "success", "message": f"Group {number} toggled!"}

if __name__ == "__main__":
    uvicorn.run(app, host="127.0.0.1", port=8000)