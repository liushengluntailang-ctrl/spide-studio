from .base import Engine


class Speed03(Engine):

    def generate(self, prompt: str) -> str:
        return f"[SPIDE Speed 0.3] {prompt}"
