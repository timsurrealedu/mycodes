const service = require('./news.service');
const { sendSuccess, sendError } = require('../../utils/response');

const createNews = async (req, res) => {
  try {
    const { title, content } = req.body;
    const news = await service.createNews({ title, content, authorId: req.user.id });
    return sendSuccess(res, 201, 'Berita berhasil dibuat.', news);
  } catch (err) {
    return sendError(res, err.status || 500, err.message || 'Internal Server Error');
  }
};

const getAllNews = async (req, res) => {
  try {
    const { title } = req.query;
    const news = await service.getAllNews(title);
    return sendSuccess(res, 200, 'Data berita berhasil diambil.', news);
  } catch (err) {
    return sendError(res, err.status || 500, err.message || 'Internal Server Error');
  }
};

const updateNews = async (req, res) => {
  try {
    const id = parseInt(req.params.id);
    const { title, content } = req.body;
    const updated = await service.updateNews(id, { title, content });
    return sendSuccess(res, 200, 'Berita berhasil diupdate.', updated);
  } catch (err) {
    return sendError(res, err.status || 500, err.message || 'Internal Server Error');
  }
};

const deleteNews = async (req, res) => {
  try {
    const id = parseInt(req.params.id);
    await service.deleteNews(id);
    return sendSuccess(res, 200, 'Berita berhasil dihapus.');
  } catch (err) {
    return sendError(res, err.status || 500, err.message || 'Internal Server Error');
  }
};

const publishNews = async (req, res) => {
  try {
    const id = parseInt(req.params.id);
    const published = await service.publishNews(id);
    return sendSuccess(res, 200, 'Berita berhasil dipublish.', published);
  } catch (err) {
    return sendError(res, err.status || 500, err.message || 'Internal Server Error');
  }
};

module.exports = { createNews, getAllNews, updateNews, deleteNews, publishNews };