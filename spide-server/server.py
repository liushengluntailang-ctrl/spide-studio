from fastapi import FastAPI
from pydantic import BaseModel

app = FastAPI(title="SPIDE Server", version="0.1.0")


class GenerateRequest(BaseModel):
    prompt: str
    engine: str = "speed03"


@app.get("/health")
def health():
    return {
        "status": "ok",
        "service": "spide-server",
        "version": "0.1.0"
    }


@app.post("/generate")
def generate(request: GenerateRequest):
    return {
        "response": f"[{request.engine}] received: {request.prompt}"
    }
