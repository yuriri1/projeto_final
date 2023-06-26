const express = require("express");
const mongoose = require("mongoose");
const State = require("./models/state");
const bodyParser = require("body-parser");
require("dotenv").config();

const porta = process.env.PORTA;
const uri = process.env.DB_URI;

const app = express();

mongoose
  .connect(uri, {
    useNewUrlParser: true,
    useUnifiedTopology: true,
  })
  .then(() => {
    console.log("Conectado ao banco de dados");
  })
  .catch((err) => {
    console.log("Erro ao conectar ao banco de dados");
    console.log(err);
  });

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

app.get("/estado", async (req, res) => {
  try {
    const result = await State.find().exec();
    console.log(result[0].state);
    res.status(200).send(result[0].state);
  } catch (error) {
    console.log(error);
  }
});

app.put("/estado", async (req, res) => {
  try {
    const result = await State.findOneAndUpdate(
      {},
      { state: req.body.state },
      { new: true }
    ).exec();
    console.log(result.state);
  } catch (error) {
    console.log(error);
  }
});

app.listen(porta, () => {
    console.log(`Servidor rodando na porta ${porta}`);
});