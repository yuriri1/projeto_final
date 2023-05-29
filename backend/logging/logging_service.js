const express = require('express')
const mongoose = require('mongoose')
const Log = require('./models/log')
const bodyParser = require('body-parser')
require('dotenv').config()


const porta = process.env.PORTA
const uri = process.env.DB_URI

const app = express()

mongoose.connect(
    uri,
    {
        useNewUrlParser: true,
        useUnifiedTopology: true
    }
).then(() => {
    console.log('Conectado ao banco de dados')
}).catch((err) => {
    console.log('Erro ao conectar ao banco de dados')
    console.log(err)
})

app.use(bodyParser.json())
app.use(bodyParser.urlencoded({ extended: true }));

app.post('/log', async (req, res) => {
    try {
        const log = new Log({
            temperature: req.body.temperature,
            date_time: req.body.date_time
        })
        await log.save()
        console.log('Log cadastrado com sucesso')
        res.status(200).send('Log cadastrado com sucesso')
    } catch (error) {
        console.log(error)
    }
})

app.listen(porta, () => {
    console.log(`Servidor rodando na porta ${porta}`)
})

