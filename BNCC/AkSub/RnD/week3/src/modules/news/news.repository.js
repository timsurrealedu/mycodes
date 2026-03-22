const { PrismaClient } = require('../../../generated/prisma');
const prisma = new PrismaClient();

const createNews = async (data) => {
  return prisma.news.create({ data });
};

const findAllNews = async (titleQuery) => {
  return prisma.news.findMany({
    where: titleQuery ? { title: { contains: titleQuery } } : {},
    include: {
      author: { select: { name: true, email: true, role: true } },
    },
    orderBy: { createdAt: 'desc' },
  });
};

const findNewsById = async (id) => {
  return prisma.news.findUnique({
    where: { id },
    include: { author: { select: { name: true, email: true } } },
  });
};

const updateNews = async (id, data) => {
  return prisma.news.update({ where: { id }, data });
};

const deleteNews = async (id) => {
  return prisma.news.delete({ where: { id } });
};

const publishNews = async (id) => {
  return prisma.news.update({
    where: { id },
    data: { published: true },
  });
};

module.exports = { createNews, findAllNews, findNewsById, updateNews, deleteNews, publishNews };