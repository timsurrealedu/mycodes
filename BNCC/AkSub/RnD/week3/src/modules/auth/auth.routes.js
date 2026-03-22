const express = require('express');
const router = express.Router();
const controller = require('./auth.controller');
const { authLimiter } = require('../../middlewares/rateLimiter.middleware');
const { verifyToken, authorizeRoles } = require('../../middlewares/auth.middleware');

router.post('/register', authLimiter, controller.register);
router.post('/login', authLimiter, controller.login);
router.patch('/assign-role', verifyToken, authorizeRoles('admin'), controller.assignRole);

module.exports = router;