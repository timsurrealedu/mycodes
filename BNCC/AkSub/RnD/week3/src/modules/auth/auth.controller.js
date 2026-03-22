const service = require('./auth.service');
const { sendSuccess, sendError } = require('../../utils/response');

const register = async (req, res) => {
  try {
    const { name, email, password, dateOfBirth } = req.body;
    if (!name || !email || !password || !dateOfBirth) {
      return sendError(res, 400, 'Semua field wajib diisi: name, email, password, dateOfBirth.');
    }
    const user = await service.register({ name, email, password, dateOfBirth });
    return sendSuccess(res, 201, 'Registrasi berhasil.', user);
  } catch (err) {
    return sendError(res, err.status || 500, err.message || 'Internal Server Error');
  }
};

const login = async (req, res) => {
  try {
    const { email, password } = req.body;
    if (!email || !password) {
      return sendError(res, 400, 'Email dan password wajib diisi.');
    }
    const result = await service.login({ email, password });
    return sendSuccess(res, 200, 'Login berhasil.', result);
  } catch (err) {
    return sendError(res, err.status || 500, err.message || 'Internal Server Error');
  }
};

const assignRole = async (req, res) => {
  try {
    const { email, role } = req.body;
    if (!email || !role) {
      return sendError(res, 400, 'Email dan role wajib diisi.');
    }
    const updated = await service.assignRole(email, role);
    return sendSuccess(res, 200, `Role user berhasil diubah menjadi ${updated.role}.`, {
      email: updated.email,
      role: updated.role,
    });
  } catch (err) {
    return sendError(res, err.status || 500, err.message || 'Internal Server Error');
  }
};

module.exports = { register, login, assignRole };