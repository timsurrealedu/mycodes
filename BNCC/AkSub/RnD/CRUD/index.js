// index.js
const express = require('express');
const { PrismaClient } = require('@prisma/client');

const app = express();
const prisma = new PrismaClient();
const PORT = 3000;

// Middleware untuk membaca JSON body
app.use(express.json());

// === CREATE: Menambah Produk ===
app.post('/products', async (req, res) => {
  const { name, category, price, stock, description } = req.body;
  try {
    const product = await prisma.product.create({
      data: { name, category, price, stock, description },
    });
    res.status(201).json({ message: 'Produk berhasil dibuat', data: product });
  } catch (error) {
    res.status(500).json({ error: error.message });
  }
});

// === READ: Mengambil Semua Produk ===
app.get('/products', async (req, res) => {
  try {
    const products = await prisma.product.findMany();
    res.json({ total: products.length, data: products });
  } catch (error) {
    res.status(500).json({ error: error.message });
  }
});

// === READ: Mengambil 1 Produk by ID ===
app.get('/products/:id', async (req, res) => {
  const { id } = req.params;
  try {
    const product = await prisma.product.findUnique({
      where: { id: Number(id) },
    });
    if (!product) return res.status(404).json({ error: 'Produk tidak ditemukan' });
    res.json({ data: product });
  } catch (error) {
    res.status(500).json({ error: error.message });
  }
});

// === UPDATE: Mengubah Data Produk ===
app.put('/products/:id', async (req, res) => {
  const { id } = req.params;
  const { name, category, price, stock, description } = req.body;
  try {
    const product = await prisma.product.update({
      where: { id: Number(id) },
      data: { name, category, price, stock, description },
    });
    res.json({ message: 'Produk berhasil diupdate', data: product });
  } catch (error) {
    // Menangani error jika ID tidak ditemukan (RecordNotFound)
    if (error.code === 'P2025') {
        return res.status(404).json({ error: 'Produk tidak ditemukan' });
    }
    res.status(500).json({ error: error.message });
  }
});

// === DELETE: Menghapus Produk ===
app.delete('/products/:id', async (req, res) => {
  const { id } = req.params;
  try {
    await prisma.product.delete({
      where: { id: Number(id) },
    });
    res.json({ message: 'Produk berhasil dihapus' });
  } catch (error) {
    if (error.code === 'P2025') {
        return res.status(404).json({ error: 'Produk tidak ditemukan' });
    }
    res.status(500).json({ error: error.message });
  }
});

// Menjalankan Server
app.listen(PORT, () => {
  console.log(`Server berjalan di http://localhost:${PORT}`);
});
