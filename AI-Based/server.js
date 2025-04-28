import express from "express";
import cors from "cors";
import { GoogleGenAI } from "@google/genai";

const app = express();
const port = 3001;

const ai = new GoogleGenAI({
    apiKey: "AIzaSyAqMJT2qU8xEh2QiGc7SWBPSXnN-9I90UY"
});

app.use(cors());
app.use(express.json());

app.post("/check", async (req, res) => {
    const { pdaDescription, inputString } = req.body;

    try {
        const prompt = `
        Given the following PDA description:
        
        ${pdaDescription}
        
        And the input string:
        
        "${inputString}"
        
        Guidelines:
        - If the PDA description mentions powers (like "a^n b^n" or "c^(n+m)"), apply counting rules.
        - If the PDA description has simple sequences (like "abc"), match sequences exactly without counting.
        - FIRST, carefully go through the PDA description, and check the input string step-by-step against the rules.
        - ONLY AFTER FULLY ANALYZING, decide if the input string should be ACCEPTED or REJECTED.
        
        At the end, clearly state:
        Result: **ACCEPTED** or **REJECTED**
        
        Also provide a short reasoning why.
        
        ⚠️ Important: DO NOT declare ACCEPTED/REJECTED before completing the full analysis.
        `


        const response = await ai.models.generateContent({
            model: "gemini-2.0-flash",
            contents: [{ role: "user", parts: [{ text: prompt }] }]
        });

        const aiText = response.candidates[0].content.parts[0].text;

        res.json({ explanation: aiText });
    } catch (error) {
        console.error(error);
        res.status(500).json({ error: "Failed to get AI response." });
    }
});

app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});
