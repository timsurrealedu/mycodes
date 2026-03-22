const bcrypt = require('bcrypt');
const jwt = require('jsonwebtoken');
const repo = require('./auth.repository');

const SALT_ROUNDS = 10;

const isPasswordValid = (password) => {
  return /[A-Z]/.test(password) && /[0-9]/.test(password);
};

const register = async ({ name, email, password, dateOfBirth }) => {
  if (!isPasswordValid(password)) {
    throw { status: 400, message: 'Password harus memiliki minimal 1 huruf kapital dan 1 angka.' };
  }

  const existing = await repo.findUserByEmail(email);
  if (existing) {
    throw { status: 409, message: 'Email sudah digunakan.' };
  }

  const hashedPassword = await bcrypt.hash(password, SALT_ROUNDS);

  const user = await repo.createUser({
    name,
    email,
    password: hashedPassword,
    role: 'reader',
    dateOfBirth: new Date(dateOfBirth),
  });

  const { password: _, ...userWithoutPassword } = user;
  return userWithoutPassword;
};

const login = async ({ email, password }) => {
  const user = await repo.findUserByEmail(email);
  if (!user) {
    throw { status: 401, message: 'Email atau password salah.' };
  }

  const isMatch = await bcrypt.compare(password, user.password);
  if (!isMatch) {
    throw { status: 401, message: 'Email atau password salah.' };
  }

  const token = jwt.sign(
    { id: user.id, email: user.email, role: user.role },
    process.env.JWT_SECRET,
    { expiresIn: process.env.JWT_EXPIRES_IN }
  );

  return { token, role: user.role, name: user.name };
};

const assignRole = async (email, role) => {
  const allowedRoles = ['writer', 'editor'];
  if (!allowedRoles.includes(role)) {
    throw { status: 400, message: 'Role hanya bisa diubah menjadi writer atau editor.' };
  }

  const user = await repo.findUserByEmail(email);
  if (!user) {
    throw { status: 404, message: 'User tidak ditemukan.' };
  }

  return repo.updateUserRole(email, role);
};

module.exports = { register, login, assignRole };