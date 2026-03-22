const { PrismaClient } = require('../../../generated/prisma');
const prisma = new PrismaClient();

const findUserByEmail = async (email) => {
  return prisma.user.findUnique({ where: { email } });
};

const createUser = async (data) => {
  return prisma.user.create({ data });
};

const updateUserRole = async (email, role) => {
  return prisma.user.update({
    where: { email },
    data: { role },
  });
};

module.exports = { findUserByEmail, createUser, updateUserRole };