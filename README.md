# SPIDE Studio

SPIDE Studio is a C++20 / Qt 6 desktop IDE with a direct SPIDE AI server connection.

## AI architecture

SPIDE Studio does NOT call Gemini directly.

```text
SPIDE Studio
    |
    v
SPIDE Server
    |
    +-- Speed 0.3
    +-- Null 0.6
    +-- Null Pro 0.5
```

The default endpoint is:

`http://localhost:8000/v1/chat/completions`

The server endpoint and model name can be changed from Settings.

The current provider accepts an OpenAI-compatible JSON response:

```json
{
  "choices": [
    {
      "message": {
        "content": "..."
      }
    }
  ]
}
```

It also accepts simple `response` or `text` fields as fallbacks.

## Build

```bash
cmake -S . -B build
cmake --build build
```

Run:

```bash
./build/spide-studio
```
