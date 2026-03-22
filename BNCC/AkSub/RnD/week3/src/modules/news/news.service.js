const repo = require('./news.repository');

const createNews = async ({ title, content, authorId }) => {
  if (!title || !content) {
    throw { status: 400, message: 'Title dan content wajib diisi.' };
  }
  return repo.createNews({ title, content, authorId });
};

const getAllNews = async (title) => {
  return repo.findAllNews(title || null);
};

const updateNews = async (id, data) => {
  const news = await repo.findNewsById(id);
  if (!news) throw { status: 404, message: 'Berita tidak ditemukan.' };
  return repo.updateNews(id, data);
};

const deleteNews = async (id) => {
  const news = await repo.findNewsById(id);
  if (!news) throw { status: 404, message: 'Berita tidak ditemukan.' };
  return repo.deleteNews(id);
};

const publishNews = async (id) => {
  const news = await repo.findNewsById(id);
  if (!news) throw { status: 404, message: 'Berita tidak ditemukan.' };
  if (news.published) throw { status: 400, message: 'Berita sudah dipublish sebelumnya.' };
  return repo.publishNews(id);
};

module.exports = { createNews, getAllNews, updateNews, deleteNews, publishNews };