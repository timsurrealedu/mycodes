require('dotenv').config();
const express = require('express');

const authRoutes = require('./modules/auth/auth.routes');
const newsRoutes = require('./modules/news/news.routes');

const app = express();

app.use(express.json());

app.use('/api/auth', authRoutes);
app.use('/api/news', newsRoutes);

app.get('/', (req, res) => {
  res.json({ message: 'News API Week 3 is running 🚀' });
});

app.use((req, res) => {
  res.status(404).json({ success: false, message: 'Route tidak ditemukan.' });
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});